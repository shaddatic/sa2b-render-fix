# How to Use the Render Fix API
## Getting the API
In order to call any API functions, you will first have to get the `RFAPI_CORE` structure pointer. This can be done in 1 of 2 ways;

1. Using one of the Render Fix user-export functions. Eg:

```cpp
extern "C" __declspec(dllexport)
void
RF_EarlyInit(const RFAPI_CORE* pApiCore, const char* path, const HelperFunctions& helperFunctions)
{
    /** pApiCore        : pointer to Core API,
        path            : path to your mod,
        helperFunctions : Mod Loader HelperFunctions **/

    // Ran just before Render Fix starts to init features
    // Your code here
}

extern "C" __declspec(dllexport)
void
RF_Init(const RFAPI_CORE* pApiCore, const char* path, const HelperFunctions& helperFunctions)
{
    /** pApiCore        : pointer to Core API,
        path            : path to your mod,
        helperFunctions : Mod Loader HelperFunctions **/

    // Ran after Render Fix has init'd features
    // Your code here
}
```

2. Or, directly getting the exported `rfapi_core` from Render Fix's dll. Eg:

```cpp
{
    const Mod* modp = helperFunctions.Mods->find("sa2-render-fix"); // Get pointer to Render Fix's mod handle

    if (modp) // Check if Render Fix is loaded
    {
        const auto* rf_api = modp->GetDllExport<const RFAPI_CORE*>("rfapi_core"); // Get dllexport

        if (rf_api) // Check the Render Fix version isn't before v1.3
        {
            // Your code here
        }
    }
}
```

The Core API is constant, so you may save it to a global variable for later use.

## Using the API
Once you have the Core API pointer, you can access the other APIs through it. It's important you check the availability of the APIs before using them, as some are only available at certain times. Here's a rundown;

```
In RF_EarlyInit : Control, Config, Render State, Shader
In RF_Init      : Config, Feature Check, Draw, Render State, Shader
Otherwise       : Feature Check, Draw, Render State, Shader
```

`Otherwise` refers to any time after Render Fix has loaded that's outside the user-exported functions, this includes your mod's `Init` function. The API pointers are also set to `NULL` when they're not available, so a temporary run-time check can be used to ensure availability. Eg:

```cpp
{
    const RFAPI_EXAMPLE* rf_exam = pApiCore->pApiExample;

    if (rf_exam)
    {
        rf_exam->func();
    }
    else // rf_draw == nullptr
    {
        puts("The Render Fix Draw API is not available");
    }
}
```

Checks like this shouldn't be in production code, however, so should only be used as a test and deleted later.

Once the API is confirmed available, you then need to check the function you wish to call is available in the current loaded version of Render Fix. Each api has a `version` member variable at its top and large span comments defining which functions were introduced in which version.

Versions are used to track when an API feature was added and if the currently loaded version of Render Fix supports it. In a perfect world, everyone would be running the latest version of everything; but that isn't the case and it needs to be accounted for it.

In the header, it looks like:

```cpp
typedef struct
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;

    void(__cdecl* func0)(void)  /* this function requires version 0 or higher       */

    /****** Version >= 1 ************************************************************/
    void(__cdecl* func1)(void)  /* this function requires version 1 or higher       */
...
```

And in your code, it would look like:

```cpp
{
    const RFAPI_EXAMPLE* rf_example = rf_api->pApiExample;

    rf_example->func0(); // Version 0, so doesn't require a check

    if (rf_example->version >= 1)
    {
        rf_example->func1(); // Version 1, so requires a check to be safe
    }
}
```

After this, you're free to use API as needed. Additional info and comments about each API and their functions can be found in the API header (`renderfix_api.h`).

## Complete Examples
User-exported function method:

```cpp
static const RFAPI_CORE* RenderFixApiPointer; // Stored for later use

extern "C" __declspec(dllexport)
void
RF_Init(const RFAPI_CORE* pApiCore, const char* path, const HelperFunctions* pHelperFunctions)
{
    /** Assume 'Example' API is version 1 of 'Core' **/

    if (pApiCore->version >= 1)
    {
        const RFAPI_EXAMPLE* rf_exam = pApiCore->pApiExample;

        /** Assume the function examples need versions 1 & 2 **/

        if (rf_exam->version >= 2)
        {
            rf_exam->func1(); // Needs version >= 1
            rf_exam->func2(); // Needs version >= 2
        }
    }

    RenderFixApiPointer = pApiCore;
}
```

Direct get method:

```cpp
extern "C" __declspec(dllexport)
void
Init(const char* path, const HelperFunctions& helperFunctions)
{
    const Mod* modp = helperFunctions.Mods->find("sa2-render-fix");

    if (modp) // Check if Render Fix is loaded
    {
        const auto* rf_api = modp->GetDllExport<const RFAPI_CORE*>("rfapi_core");

        /** Assume 'Example' API is version 0 of 'Core' **/

        if (rf_api) // Check the API exists, no version check needed
        {
            const RFAPI_EXAMPLE* rf_exam = rf_api->pApiExample;

            /** Assume the function examples need versions 1 & 2 **/

            if (rf_exam->version >= 2)
            {
                rf_exam->func1(); // Needs version >= 1
                rf_exam->func2(); // Needs version >= 2
            }
        }
    }
}
```
