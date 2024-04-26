# How to Use the Render Fix API
## User-Exported Functions
### Rundown
Render Fix is capable of calling a particular set of functions in your mod directly, these are called "user-exported functions". These functions are called `RF_EarlyInit` & `RF_Init`, & both are called at different times during Render Fix's boot process:

- `RF_EarlyInit`
  - Called just before RF begins to init its own features, this makes it useful for controling RF or other time sensitive actions, such as replacing files that haven't been loaded yet. However, because RF isn't done booting, its use cases are limited.
- `RF_Init`
  - Called at the end of RF's boot process. Since RF is done booting, almost all of the API features are available. However, actions such as replacing files will have no effect at this stage, since all features are done loading.

If you are unsure which of the two you should use, use `RF_Init`.

### How to Make Them
In order for Render Fix to find your exported functions, you need give them the correct name, parameters and order of parameters, mark them as exported, and finally ensure they are marked as `extern "C"`. I'll go through each of the steps then show you some examples:

1. Name: You already know their names (`RF_Init`/`RF_EarlyInit`).

2. Parameters: The params from left to right are:
    1. `const RFAPI_CORE*`, this is a pointer to RF's Core API
    2. `const char*`, this is a string path to _your_ mod's folder
    3. `const HelperFunctions&`, this is a reference/pointer to the modloader's HelperFunctions.

3. Marking as exported: By adding `__declspec(dllexport)` to your function definition, you tell Visual Studio to make that function exported. This will allow Render Fix to search and find your function. This is the same as a mod's regular `Init` function.

4. Marking as `extern "C"`: You can do this by either adding `extern "C"` to your function definition, or placing the function in an `extern "C"` block using `{` & `}` symbols. This is the same as a mod's regular `Init` function.

### Examples
With those points layed out, here's examples of both functions:

```cpp
extern "C" __declspec(dllexport) // Mark as extern "C" and as exported
void
RF_EarlyInit(const RFAPI_CORE* pApiCore, const char* path, const HelperFunctions& helperFunctions)
{
    // Ran just before Render Fix starts to init features
    // Your code here
}

extern "C" __declspec(dllexport) // Mark as extern "C" and as exported
void
RF_Init(const RFAPI_CORE* pApiCore, const char* path, const HelperFunctions& helperFunctions)
{
    // Ran after Render Fix has init'd features
    // Your code here
}
```

The examples marked each function individually as `extern "C"`, but placing them in a `extern "C"` block with `{` & `}` symbols would work the same.

## Getting the API
In order to call any API functions, you will first have to get the `RFAPI_CORE` structure pointer. This can be done in 1 of 2 ways;

1. Using one of the Render Fix user-exported functions. Or,
2. Directly getting the exported `rfapi_core` from Render Fix's dll. Eg:

```cpp
...
    const Mod* modp = helperFunctions.Mods->find("sa2-render-fix"); // Get pointer to Render Fix's mod handle

    if (modp) // Check if Render Fix is loaded
    {
        const auto* rf_api = modp->GetDllExport<const RFAPI_CORE*>("rfapi_core"); // Get dllexport

        if (rf_api) // Check the Render Fix API was found/exists
        {
            // Your code here
        }
    }
...
```

When directly getting the API, it's important you check if the API exists as Render Fix versions before 1.3 did not include any API. If the user happens to be using one of these earlier versions, you much check for it and handle it. The user-exported functions don't need this check, as earlier versions of Render Fix simply won't call those functions.

The Core API is also constant, so you may save it to a global variable for later use.

## Using the API
Once you have the Core API pointer, you can access the other APIs through it. It's important you check the availability of the APIs before using them, as some are only available at certain times. Here's a rundown;

```
In RF_EarlyInit : Control, Config, Render State, Shader
In RF_Init      : Config, Feature Check, Draw, Render State, Shader
Otherwise       : Feature Check, Draw, Render State, Shader
```

`Otherwise` refers to any time after Render Fix has loaded that's outside the user-exported functions, this includes your mod's `Init` function. The API pointers are also set to `NULL` when they're not available, so a temporary run-time check can be used to ensure availability. Checks like this shouldn't be in production code, however, so should only be used as a test and deleted later.

Additionally, some APIs may only be available in later versions of Render Fix than the one the user has loaded. In a perfect world, everyone would be running the latest version of everything; but that isn't the case and it needs to be accounted for. To check for this, use the `version` member in `RFAPI_CORE` to check if the API you whish to use is available in the loaded version of Render Fix. For example:

In the header, it looks like:
```cpp
typedef struct // RFAPI_CORE example
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;

    /**** Mod version ****/
    RF_VERSION rf_version;                      /* current Render Fix version       */
...
    /****** Version >= 1 ************************************************************/
    const RFAPI_EXAMPLE*     pApiExample;      /* Example API                       */
...
```
This tells us that the Example API requires version 1 or above. In your code, a check would look like:
```cpp
...
    if (rf_api->version >= 1)
    {
        const RFAPI_EXAMPLE* rf_example = rf_api->pApiExample;

        // Use the Example API here
    }
...
```

Once the API is confirmed available, you then need to check the function you wish to call is also available in the current loaded version of Render Fix. Just like the Core API, each individual API also has a `version` member variable at its top and large span comments defining which functions were introduced in which version. Luckily, the process is exactly the same as the Core API, eg:

```cpp
...
    const RFAPI_EXAMPLE* rf_example = rf_api->pApiExample;

    /** Assume the function needs version 1 or higher **/

    if (rf_example->version >= 1) // Check RFAPI_EXAMPLE version
    {
        rf_example->func();
    }
...
```

After this, you're free to use API as needed. Additional info and comments about each API and their functions can be found in the API header (`renderfix_api.h`).

## Complete Examples
User-exported function method:
```cpp
extern "C" __declspec(dllexport)
void
RF_Init(const RFAPI_CORE* pApiCore, const char* path, const HelperFunctions& helperFunctions)
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

        /** Assume 'Example' API is version 1 of 'Core' **/

        if (rf_api && rf_api->version >= 1) // Check the API exists, and check version
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
