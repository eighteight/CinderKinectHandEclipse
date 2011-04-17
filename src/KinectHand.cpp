#include "cinder/app/AppBasic.h"

#include "cinder/Utilities.h"

#include <XnOpenNI.h>
#include "XnCppWrapper.h"
#include <XnHash.h>
#include <XnLog.h>

// Header for NITE
#include "XnVNite.h"

typedef enum
{
	IN_SESSION,
	NOT_IN_SESSION,
	QUICK_REFOCUS
} SessionState;

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace xn;

#define SAMPLE_XML_PATH "/Users/boba/repos/Nite-1.3.0.18/Data/Sample-Tracking.xml"
#define CHECK_RC(rc, what)                                   \
if (rc != XN_STATUS_OK)                                      \
{                                                            \
    printf("%s failed: %s\n", what, xnGetStatusString(rc));               \
}

#define CHECK_ERRORS(rc, errors, what)		\
	if (rc == XN_STATUS_NO_NODE_PRESENT)	\
	{										\
		XnChar strError[1024];				\
		errors.ToString(strError, 1024);	\
		printf("%s\n", strError);			\
		return (rc);						\
	}

#define GESTURE_CLICK "Click"
#define GESTURE_WAVE "Wave"

XnBoundingBox3D* boundingBox;
xn::GestureGenerator g_GestureGenerator;
xn::HandsGenerator g_HandsGenerator;

// OpenNI objects
xn::Context context;
xn::DepthGenerator g_DepthGenerator;

// NITE objects
XnVSessionManager* g_pSessionManager;
XnVFlowRouter* g_pFlowRouter;

SessionState g_SessionState = NOT_IN_SESSION;

class KinectHand : public AppBasic {
 public:
	void    setup();
	void    draw();
	void    update();
	void 	mouseDrag( MouseEvent event );
	void 	keyDown( KeyEvent event );

	static void XN_CALLBACK_TYPE Gesture_Recognized(GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pIDPosition, const XnPoint3D* pEndPosition, void* pCookie);
	static void XN_CALLBACK_TYPE Gesture_Process(GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pPosition, XnFloat fProgress, void* pCookie);
	static void XN_CALLBACK_TYPE Hand_Update(HandsGenerator& generator, XnUserID nId, const XnPoint3D* pPosition, XnFloat fTime, void* pCookie);
	static void XN_CALLBACK_TYPE Hand_Create(xn::HandsGenerator& generator, XnUserID nId, const XnPoint3D* pPosition, XnFloat fTime, void* pCookie);
	static void XN_CALLBACK_TYPE Hand_Destroy(xn::HandsGenerator& generator, XnUserID nId, XnFloat fTime, void* pCookie);
	static void XN_CALLBACK_TYPE NoHands(void* UserCxt);
	static void XN_CALLBACK_TYPE FocusProgress(const XnChar* strFocus, const XnPoint3D& ptPosition, XnFloat fProgress, void* UserCxt);
	static void XN_CALLBACK_TYPE SessionStarting(const XnPoint3D& ptPosition, void* UserCxt);
	static void XN_CALLBACK_TYPE SessionEnding(void* UserCxt);

};

void KinectHand::setup()
{
	std::cout << "Setting application path: " << getPathDirectory(getAppPath()) << std::endl;
	chdir( getPathDirectory(getAppPath()).c_str() );

	XnStatus rc = XN_STATUS_OK;
	xn::EnumerationErrors errors;

	// Initialize OpenNI
	rc = context.InitFromXmlFile(SAMPLE_XML_PATH, &errors);
//	CHECK_ERRORS(rc, errors, "InitFromXmlFile");
	CHECK_RC(rc, "InitFromXmlFile");

	rc = context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
	CHECK_RC(rc, "Find depth generator");
	rc = context.FindExistingNode(XN_NODE_TYPE_HANDS, g_HandsGenerator);
	CHECK_RC(rc, "Find hands generator");
//
	// Create NITE objects
	g_pSessionManager = new XnVSessionManager;
	rc = g_pSessionManager->Initialize(&context, "Click,Wave", "RaiseHand");
	CHECK_RC(rc, "SessionManager::Initialize");
//
	g_pSessionManager->RegisterSession(NULL, SessionStarting, SessionEnding, FocusProgress);

    XnStatus nRetVal = XN_STATUS_OK;

    nRetVal = g_GestureGenerator.Create(context);
    nRetVal = g_HandsGenerator.Create(context);
    CHECK_RC(nRetVal, "Create Gesture & Hands Generators");
    // Register to callbacks
    XnCallbackHandle h1, h2;
    g_GestureGenerator.RegisterGestureCallbacks(Gesture_Recognized, Gesture_Process, NULL, h1);
    g_HandsGenerator.RegisterHandCallbacks(Hand_Create, Hand_Update, Hand_Destroy, NULL, h2);
    //Make it start generating data
    nRetVal = context.StartGeneratingAll();
    CHECK_RC(nRetVal, "Start Generating All Data");
    nRetVal = g_GestureGenerator.AddGesture(GESTURE_CLICK, boundingBox);
    nRetVal = g_GestureGenerator.AddGesture(GESTURE_WAVE, boundingBox);
}


void KinectHand::update() {
	XnStatus nRetVal = context.WaitAnyUpdateAll();
    CHECK_RC(nRetVal, "Wait and Update");
}

void KinectHand::draw() {
}

void KinectHand::mouseDrag( MouseEvent event ) {
}

void KinectHand::keyDown( KeyEvent event ) {
}


void XN_CALLBACK_TYPE KinectHand::Gesture_Recognized(GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pIDPosition, const XnPoint3D* pEndPosition, void* pCookie)
{
	printf("Gesture recognized: %s\n", strGesture);
	g_GestureGenerator.RemoveGesture(strGesture);
	g_HandsGenerator.StartTracking(*pEndPosition);
}

void XN_CALLBACK_TYPE KinectHand::Gesture_Process(GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pPosition, XnFloat fProgress, void* pCookie) {
	printf("Gesture process: %s\n", strGesture);
    printf("Gesture Process: (%f,%f,%f)\n", pPosition->X, pPosition->Y, pPosition->Z);
}

void XN_CALLBACK_TYPE KinectHand::Hand_Create(xn::HandsGenerator& generator, XnUserID nId, const XnPoint3D* pPosition, XnFloat fTime, void* pCookie)
{
	printf("New Hand: %d @ (%f,%f,%f)\n", nId, pPosition->X, pPosition->Y, pPosition->Z);
}

void XN_CALLBACK_TYPE KinectHand::Hand_Update(HandsGenerator& generator, XnUserID nId, const XnPoint3D* pPosition, XnFloat fTime, void* pCookie) {
	 printf("Update Hand: %d @ (%f,%f,%f)\n", nId, pPosition->X, pPosition->Y, pPosition->Z);
}
void XN_CALLBACK_TYPE KinectHand::Hand_Destroy(xn::HandsGenerator& generator, XnUserID nId, XnFloat fTime, void* pCookie)
{
	printf("Lost Hand: %d\n", nId);
	g_GestureGenerator.AddGesture(GESTURE_CLICK, NULL);
}

// Callback for when the focus is in progress
void XN_CALLBACK_TYPE KinectHand::FocusProgress(const XnChar* strFocus, const XnPoint3D& ptPosition, XnFloat fProgress, void* UserCxt)
{
	printf("Focus progress: %s @(%f,%f,%f): %f\n", strFocus, ptPosition.X, ptPosition.Y, ptPosition.Z, fProgress);
}
// callback for session start
void XN_CALLBACK_TYPE KinectHand::SessionStarting(const XnPoint3D& ptPosition, void* UserCxt)
{
	printf("Session start: (%f,%f,%f)\n", ptPosition.X, ptPosition.Y, ptPosition.Z);
	g_SessionState = IN_SESSION;
}
// Callback for session end
void XN_CALLBACK_TYPE KinectHand::SessionEnding(void* UserCxt)
{
	printf("Session end\n");
	g_SessionState = NOT_IN_SESSION;
}
void XN_CALLBACK_TYPE KinectHand::NoHands(void* UserCxt)
{
	if (g_SessionState != NOT_IN_SESSION)
	{
		printf("Quick refocus\n");
		g_SessionState = QUICK_REFOCUS;
	}
}


CINDER_APP_BASIC( KinectHand, RendererGl );
