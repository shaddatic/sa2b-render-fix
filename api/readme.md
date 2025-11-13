# How to Use the Render Fix API
## Rundown
This file goes over the basics of using the Render Fix API. If you've used the Input Controls API or the SASDL API, then the process here is almost exactly the same. If not, continue reading!

To start, it's recommended that you have at least a basic understanding of C/C++ before using the API - this readme assumes you already have knowledge on the foundations of the language.

The SA2 Render Fix API - aka the RF API, or just RFAPI - is the user interface to the mod and it's features. It allows you to use and check for Render Fix features that would otherwise be locked to the mod itself, giving you more control of how your mod looks.

The "API" itself is a set of structures, individually called "modules", which contain basic version info and function pointers that give you direct access to the internal functions of the mod. You can get the API in a few ways, but the main way is allowing Render Fix to call a special, exported functionm in your mod; this functions is called `RFAPI_Init`. There are other exported functions too - `RFAPI_Early` and `RFAPI_Late` - that have more specific use cases involving *when* they're called. For this we'll only go over the standard `RFAPI_Init`, but we'll briefly touch on the others too.

This may sound complicated, but the process is actually pretty simple and I'll walk you through it step by step. It is recommended that you have the API headers open while you read this, to give additional context as I explain things.

## Step by Step
### The API Headers
First, you need to import the API headers into your project. This can be done any way you like, including just copying them. The headers are important as they define the API structures and types; without them, you and your code will be blind.

Once it's in your project, make sure to `#include` it in any source files that will be using the API directly. It's recommended to make a seperate source file specifically to handle the API, essentially making "wrapper" functions for your own mod, although it's not necessary.

Not all API modules/structures can be used at the same time, some might only have a small window of availablity. These times are clearly labled at the top of headers, and look like this.

```
*   Availability:
*     - Before Init     : No
*     - At Init         : Partial, X will be null
*     - After Init      : Yes
```

Each entry is defined as:

- `Before Init`: Any time before or during `RFAPI_Early`
- `At Init    `: Only during `RFAPI_Init`
- `After Init `: Any time during or after `RFAPI_Late`, which includes in-game

In this example case, the API module can be used in `RFAPI_Late` and in-game, but it's only partially available during `RFAPI_Init` and not available at all in `RFAPI_Early` (as most things aren't, as the mod hasn't started the init process yet). Attempting to use an API outside of it's availablity window is usually undefined behavior, so make sure to double check this before using anything.

Every callable function also has a description to help you use them as intended. For example:

```c
/*
*   Description:
*     Takes a list of things, and does stuff to them.
* 
*   Parameters:
*     - pThings     : pointer to things
*     - nbThings    : number of things
*/
void (__cdecl* example_v0)( thing* pThings, int nbThings );
```

It's normally more descriptive than this example, but you can see the function explaining how to use it and what each parameters does. Follow these carefully.

Over time, the API will be expanded to support new features. When this happens the structure `version` - a struct member located directly at the top - will be increased, it looks like this:

```c
typedef struct
{
    uint32_t version;                   /* structure version                                    */
    
    /****** Version >= 0 ************************************************************************/
    /*
    *   ...
    */
    void (__cdecl* example_v0)( ... );  /* member example, v0                                   */
    
    /****** Version >= 1 ************************************************************************/
    /*
    *   ...
    */
    void (__cdecl* example_v1)( ... );  /* member example, v1                                   */
...
```

You can also see here the large span comments seperating what each version supports. These versions start at `0`, indicating no changes since release. In this case, a `version` of `1` indicates `example_v0` and `example_v1` are available, but a `version` of `0` means only `example_v0` is available and that attempting to use `example_v1` will likely crash. It's important you refer to the version variable when calling API functions, as the user may have an older version that doesn't include the function you wish to call yet.

With this, you can also enforce a minimum API version that your mod will work with. Try not to just set this to the latest version though, take a second to see what the lowest version you can use is so as many people as possible can enjoy your mod!

Now that you have the headers and structures, you need to actually get the API. This is pretty easy, so let's go through it.

### Getting the API
In order to use the API, you need to actually get it somehow. This can be done in 1 of 2 ways:

1. Creating a user-exported function - eg. `RFAPI_Init` - for the API to call your mod. (Recommended)
2. Directly getting the API from Render Fix's DLL handle.

Method '2' should be avoided, and it's only an option for power-users who have some specific use case the regular method doesn't fill. We will be using method '1' going forward.

With that out of the way, what is a "user-exported function" and how do we make one?

### User-Exported Functions
The API is capable of calling a special set of functions in your mod directly, these are named "user-exported functions". They are very similar to the normal `Init` functions DLL mods have to make; if you've made one of those, this part will be a breeze.

For Render Fix, the main user-exported function is called `RFAPI_Init`. There are also two others named `RFAPI_Early` and `RFAPI_Late`, which are called before and after Render Fix's own `Init` process - these have a narrow use case though so we'll focus on `RFAPI_Init`, but they are otherwise all the same excluding the call time. There's also the legacy `RF_Init` and `RF_EarlyInit`, but these shouldn't be used and are only there for older mods pre-1.5; they may be removed in a later update.

Here's a crude example of `RFAPI_Init` for us to dissect:

```cpp
extern "C" __declspec(dllexport)
int32_t RFAPI_Init(const RFAPI* pApi, const char* puPath, const HelperFunctions* pHelpFuncs, size_t ixMod)
{
    // return value must be 0
    return 0;
}
```

Now, a lot is going on there, but let's break it down:            
1. `extern "C"`:   
    This makes the function name fixed, it's otherwise random* - this is only needed when using C++. You can also place the function in an `extern "C"` block using `{` & `}`, either way works.
2. `__declspec(dllexport)`: 
    This marks the function to be exported from your DLL file. This will allow the API to search for and find your function using its name.
3. Return Type/Value (`int32_t`): 
    This is the return type of the function. The function must `return 0` once it's done. The return value currently isn't used but may be in the future, so it's important all current mods return the same, standard value.
4. Parameters: 
    The params from left to right are:
    1. `const RFAPI*`           : this is a pointer to the core API structure        
    2. `const char*`            : this is a string path to *your* mod's folder (in UTF-8 if you were curious)
    3. `const HelperFunctions*` : this is a pointer to the Mod Loader's Helper Functions    
    4. `size_t`                 : this is a mod position index of *your* mod, if you wish to use it

\*It's not actually random, there is method to the madness. But it's a lot harder to work with and would restrict the API to C++ only.

All user-exported functions are ran during the Render Fix's own `Init` function, these means you can't guarantee when your user-exported function will run compared to your own `Init` function. Because of this, it's not recommended to access the API inside of your `Init` function and to either restrict it to your exported API function, or just wait until the game is actually running - after all `Init`s have been called. This *also* means you can't use the user-exported API function to check if the API is installed, that should be done seperately with the `ModInfo` stuff given by the Mod Loader.

Now that you have the API, it's time to make use of it.

### Using the API
Once you have the API pointer, it's up to you how you use it! It's recommeneded you save any pointers you want to use for later - either by saving only the main pointer, saving each module pointer, or by saving each individual function pointer as needed. The pointers are constant for the lifetime of the program and none of the structures will be changed or free'd after you're given them.

Now, let's do some full examples!

## Complete Examples
Checking each API structure version individually:
```c
extern "C" __declspec(dllexport)
int32_t RFAPI_Init(const RFAPI* pApi, const char* puPath, const HelperFunctions* pHelpFuncs, size_t ixMod)
{
    if ( pApi->version >= 1 )                            // core module 'version' Check
    {
        const RFAPI_MODULE* p_module = pApi->pModuleApi; // module available in 'core' version 1

        if ( p_module->version >= 1 )                    // module 'version' check
        {
            p_module->example_v0( ... );                 // function available in version 0
            p_module->example_v1( ... );                 // function available in version 1
        }
    }

    // return value must be 0
    return 0;
}
```

Checking the Render Fix mod version:
```c
extern "C" __declspec(dllexport)
int32_t RFAPI_Init(const RFAPI* pApi, const char* puPath, const HelperFunctions* pHelpFuncs, size_t ixMod)
{
    if ( RFAPI_CHECKVER( pApi, 1,5,0,0 ) ) // equal or higher than v1.5.0.0
    {
        const RFAPI_MODULE* p_module = pApi->pModuleApi;
            
        p_module->example_v0( ... );    // function available in version 0, part of v1.3.0
        p_module->example_v1( ... );    // function available in version 1, part of v1.5.0
    }

    // return value must be 0
    return 0;
}
```

Using API after Init:
```c
const RFAPI_MODULE* ModuleApi;

void FunctionThatRunsLater(void)
{
    if ( ModuleApi )
    {
        ModuleApi->example_v0( ... );
        ModuleApi->example_v1( ... );
    }
}

extern "C" __declspec(dllexport)
int32_t RFAPI_Init(const RFAPI* pApi, const char* puPath, const HelperFunctions* pHelpFuncs, size_t ixMod)
{
    if ( pApi->version >= 1 )                            // core module 'version' Check
    {
        const RFAPI_MODULE* p_module = pApi->pModuleApi; // module available in 'core' version 1

        if ( p_module->version >= 1 )                    // module 'version' check
        {
            ModuleApi = p_module;
        }
    }

    // return value must be 0
    return 0;
}
```

## Additional Notes
The API will never have breaking changes. Names may change, but your old code will always continue work. Sometimes functions are depricated, but continued suppport of old mods is a top priority. At worst, a function will just do nothing past a point, but that is always a last resort when all else has failed.

The examples used a `const HelperFunctions*` for user-exported function parameters, this is exactly the same as a `const HelperFunctions&` just used a bit differently - the compiled code underneath is exactly the same. So, either is fine.

These examples were in C++, as that's most commonly used by modders, but it all works the same in C. If you're using C, I'm sure you can figure out what you need to change on your own.
