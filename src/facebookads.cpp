// Extension lib defines
#define EXTENSION_NAME FacebookAds
#define LIB_NAME "FacebookAds"
#define MODULE_NAME LIB_NAME
#define DLIB_LOG_DOMAIN LIB_NAME

// Defold SDK
#include <dmsdk/sdk.h>
#include <dmsdk/dlib/log.h>

#if defined(DM_PLATFORM_ANDROID)


static JNIEnv* Attach()
{
    JNIEnv* env;
    JavaVM* vm = dmGraphics::GetNativeAndroidJavaVM();
    vm->AttachCurrentThread(&env, NULL);
    return env;
}

static bool Detach(JNIEnv* env)
{
    bool exception = (bool) env->ExceptionCheck();
    env->ExceptionClear();
    JavaVM* vm = dmGraphics::GetNativeAndroidJavaVM();
    vm->DetachCurrentThread();
    return !exception;
}

namespace {
struct AttachScope
{
    JNIEnv* m_Env;
    AttachScope() : m_Env(Attach())
    {
    }
    ~AttachScope()
    {
        Detach(m_Env);
    }
};

struct Facebook {
    Facebook()
    {
        memset(this, 0, sizeof(*this));
    }
    // void Update();
    jobject m_FB;
    jclass m_FacebookAdsClass;
    // jmethodID m_Public;
    jmethodID m_Initialize;
    jmethodID m_LoadInterstitial;
    jmethodID m_LoadRewardedVideo;
    jmethodID m_ShowInterstitial;
    jmethodID m_ShowRewardedVideo;
    jmethodID m_LoadBanner;
    jmethodID m_ShowBanner;
    jmethodID m_HideBanner;
};

}

// Facebook::Update(){
//     dmLogInfo("heh ........");
// }

static jclass GetClass(JNIEnv* env, const char* classname)
{
    jclass activity_class = env->FindClass("android/app/NativeActivity");
    jmethodID get_class_loader = env->GetMethodID(activity_class,"getClassLoader", "()Ljava/lang/ClassLoader;");
    jobject cls = env->CallObjectMethod(dmGraphics::GetNativeAndroidActivity(), get_class_loader);
    jclass class_loader = env->FindClass("java/lang/ClassLoader");
    jmethodID find_class = env->GetMethodID(class_loader, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

    jstring str_class_name = env->NewStringUTF(classname);
    jclass outcls = (jclass)env->CallObjectMethod(cls, find_class, str_class_name);
    env->DeleteLocalRef(str_class_name);
    return outcls;
}



static Facebook g_Facebook; // global facebook object 

static void InitFacebookExtension(){
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;

    g_Facebook.m_FacebookAdsClass = GetClass(env, "com.b4dnetwork.extensions.JFacebookAds");
    jmethodID jni_constructor = env->GetMethodID(g_Facebook.m_FacebookAdsClass, "<init>", "(Landroid/app/Activity;)V"); //TODO delete later
    g_Facebook.m_FB = env->NewGlobalRef(env->NewObject(g_Facebook.m_FacebookAdsClass, jni_constructor, dmGraphics::GetNativeAndroidActivity()));

    
    // g_Facebook.m_Public = env->GetMethodID(g_Facebook.m_FacebookAdsClass, "Public", "(Ljava/lang/String;)Ljava/lang/String;");
    g_Facebook.m_Initialize = env->GetMethodID(g_Facebook.m_FacebookAdsClass, "Initialize", "(Landroid/app/Activity;)V");
    g_Facebook.m_LoadInterstitial = env->GetMethodID(g_Facebook.m_FacebookAdsClass, "LoadInterstitial", "(Ljava/lang/String;)V");
    g_Facebook.m_LoadRewardedVideo = env->GetMethodID(g_Facebook.m_FacebookAdsClass, "LoadRewardedVideo", "(Ljava/lang/String;)V");
    g_Facebook.m_LoadBanner = env->GetMethodID(g_Facebook.m_FacebookAdsClass, "LoadBanner", "(Ljava/lang/String;)V");
    g_Facebook.m_ShowInterstitial = env->GetMethodID(g_Facebook.m_FacebookAdsClass, "ShowInterstitial", "()V");
    g_Facebook.m_ShowRewardedVideo = env->GetMethodID(g_Facebook.m_FacebookAdsClass, "ShowRewardedVideo", "()V");
    g_Facebook.m_ShowBanner = env->GetMethodID(g_Facebook.m_FacebookAdsClass, "ShowBanner", "()V");
    g_Facebook.m_HideBanner = env->GetMethodID(g_Facebook.m_FacebookAdsClass, "HideBanner", "()V");
   
    dmLogInfo("InitFacebookExtension ........");
}

// static int Public(lua_State* L)
// {
//     AttachScope attachscope;
//     JNIEnv* env = attachscope.m_Env;
//     DM_LUA_STACK_CHECK(L, 1);

//     const char* text_lua = luaL_checkstring(L,1);
//     jstring text = env->NewStringUTF(text_lua); // TODO : delete later

//     jstring return_value = (jstring)env->CallObjectMethod(g_Facebook.m_FB , g_Facebook.m_Public , text);
//     lua_pushstring(L, env->GetStringUTFChars(return_value, 0));

//     // env->DeleteLocalRef(text);
//     env->DeleteLocalRef(return_value);
//     return 1;
// }

static int Initialize(lua_State* L){
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;

    env->CallVoidMethod(g_Facebook.m_FB , g_Facebook.m_Initialize , dmGraphics::GetNativeAndroidActivity());
    dmLogInfo("FB Ads Initialize ........");
    return 0;
}

static int LoadInterstitial(lua_State* L){
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    //DM_LUA_STACK_CHECK(L, 1);

    const char* lua_placement_id = luaL_checkstring(L,1);
    jstring placement_id = env->NewStringUTF(lua_placement_id); 

    env->CallVoidMethod(g_Facebook.m_FB , g_Facebook.m_LoadInterstitial , placement_id);
    env->DeleteLocalRef(placement_id);
    return 0;
}


static int ShowInterstitial(lua_State* L){
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;

    env->CallVoidMethod(g_Facebook.m_FB , g_Facebook.m_ShowInterstitial);
    return 0;
}


static int LoadRewardedVideo(lua_State* L){
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    //DM_LUA_STACK_CHECK(L, 1);

    const char* lua_placement_id = luaL_checkstring(L,1);
    jstring placement_id = env->NewStringUTF(lua_placement_id); 

    env->CallVoidMethod(g_Facebook.m_FB , g_Facebook.m_LoadRewardedVideo , placement_id);
    env->DeleteLocalRef(placement_id);
    return 0;
}


static int ShowRewardedVideo(lua_State* L){
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;

    env->CallVoidMethod(g_Facebook.m_FB , g_Facebook.m_ShowRewardedVideo);
    return 0;
}


static int LoadBanner(lua_State* L){
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    //DM_LUA_STACK_CHECK(L, 1);

    const char* lua_placement_id = luaL_checkstring(L,1);
    jstring placement_id = env->NewStringUTF(lua_placement_id); 

    env->CallVoidMethod(g_Facebook.m_FB , g_Facebook.m_LoadBanner ,  placement_id);
    env->DeleteLocalRef(placement_id);
    return 0;
}

static int ShowBanner(lua_State* L){
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;

    env->CallVoidMethod(g_Facebook.m_FB , g_Facebook.m_ShowBanner);
    return 0;
}

static int HideBanner(lua_State* L){
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;

    env->CallVoidMethod(g_Facebook.m_FB , g_Facebook.m_HideBanner);
    return 0;
}



// Functions exposed to Lua
static const luaL_reg Module_methods[] =
{
    {"initialize", Initialize},
    {"load_interstitial", LoadInterstitial},
    {"show_interstitial", ShowInterstitial},
    {"load_rewarded_video", LoadRewardedVideo},
    {"show_rewarded_video", ShowRewardedVideo},
    {"load_banner", LoadBanner},
    {"show_banner", ShowBanner},
    {"hide_banner", HideBanner},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeExtension(dmExtension::Params* params)
{
    // Init Lua
    LuaInit(params->m_L);
    InitFacebookExtension();
    printf("Registered %s Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#else //if not defined(DM_PLATFORM_ANDROID) (other platfrom)

static dmExtension::Result AppInitializeExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#endif // if defined(DM_PLATFORM_ANDROID)

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeExtension, AppFinalizeExtension, InitializeExtension, 0, 0, FinalizeExtension)