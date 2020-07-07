// Extension lib defines
#define EXTENSION_NAME FacebookAds
#define LIB_NAME "FacebookAds"
#define MODULE_NAME LIB_NAME

// Defold SDK
#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID)
#include <jni.h>


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
}

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

static int DoStuffJava(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;

    jclass cls = GetClass(env, "com.b4dnetwork.extensions.JFacebookAds");
    jmethodID method = env->GetStaticMethodID(cls, "DoStuff", "()Ljava/lang/String;");
    
    jstring return_value = (jstring)env->CallStaticObjectMethod(cls, method);
    lua_pushstring(L, env->GetStringUTFChars(return_value, 0));
    env->DeleteLocalRef(return_value);
    return 1;
}

// static int Initialize(lua_State* L)
// {
//     AttachScope attachscope;
//     JNIEnv* env = attachscope.m_Env;

//     jclass cls = GetClass(env, "com.b4dnetwork.extensions.JFacebookAds");
//     jmethodID method = env->GetMethodID(cls, "Initialize", "(Landroid/content/Context;)V");
    
//     env->CallVoidMethod(cls, method , dmGraphics::GetNativeAndroidActivity());

//     return 0;
// }

static int Fuck(lua_State* L)
{
    //DM_LUA_STACK_CHECK(L, 1);
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;

    //const char* text_lua = luaL_checkstring(L,1);
    //jstring text = env->NewStringUTF(text_lua);

    jclass cls = GetClass(env, "com.b4dnetwork.extensions.JFacebookAds");
    jmethodID method = env->GetMethodID(cls, "Fuck", "()Ljava/lang/String;");
    
    jstring return_value = (jstring)env->CallObjectMethod(cls, method);
    lua_pushstring(L, env->GetStringUTFChars(return_value, 0));
    env->DeleteLocalRef(return_value);
    return 1;
}



// static int LoadInterstitial(lua_State* L)
// {
    
//     AttachScope attachscope;
//     JNIEnv* env = attachscope.m_Env;
    
//     //Placement Id
//     char placementId_lua = luaL_checkstring(L,1);

//     jclass cls = GetClass(env, "com.b4dnetwork.extensions.JFacebookAds");
//     jmethodID method = env->GetMethodID(cls, "LoadInterstitial", "(Landroid/content/Context;Ljava/lang/String)V");
    
//     env->CallVoidMethod(cls, method , dmGraphics::GetNativeAndroidActivity() , placementId_lua);

//     return 0;
// }



// Functions exposed to Lua
static const luaL_reg Module_methods[] =
{
    {"dostuff_java", DoStuffJava},
    {"fuck", Fuck},
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

#else

static dmExtension::Result AppInitializeExtension(dmExtension::AppParams* params)
{
    dmLogWarning("Registered %s (null) Extension\n", MODULE_NAME);
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

#endif

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeExtension, AppFinalizeExtension, InitializeExtension, 0, 0, FinalizeExtension)