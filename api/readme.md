# How to Use the Render Fix API
## Rundown
If you've used the SA2 Input Controls API, the process for Render Fix is exactly the same. If not, continue reading!

The Render Fix API is the user interface for Render Fix and its features. Using it, you can control how the mod functions by turning on and off features or use tools and utilities that otherwise only Render Fix would have access to.

There are a lot of uses for the API so, to make it easier, they're seperated into smaller API modules that all surround a single use. For example, the 'Font' API is all about custom fonts; on the other hand, the 'Draw' API is for drawing things to the screen.

Each API module is accessed through a single structure, called the 'Core' API. It's this that you will be getting from Render Fix to gain access to the API as a whole.

How these functions are used is up to you, but *when* they're used is more fixed. Certain functions need to be ran before certain times for RF to have the oportunity to act on them. For most functions it doesn't matter, but it's always important to check when functions are available before using them.

But it's not just when they can be used, it's also when they were added. The Render Fix API is always growing, so it's important to make sure functions are available in the RF version currently installed. This check is easy, but it can also be easy to forget so always double check.

It may sound complicated, but I promise it's simpler than it looks and I'm going to walk you through it in this readme. It is also recommended that you have the API header open while you read through this, that way you have additional context as I explain things.

So, let's start.

## The API Header
First, you need to import the API header into your project. This can be done any way you like, including just copying it. The header is important as it defines the API structures and types, and without them you're not calling anything.

Once it's in your project, make sure to include it in any source files that will be using the API directly.

Now, you need to actually get the API from Render Fix. This is pretty easy, so let's go through it.

## Getting the API
In order to call any API functions, you will first have to get the `RFAPI_CORE` structure pointer. This can be done in 1 of 2 ways;
              
1. Using one of the Render Fix user-exported functions.             (Recommended)
2. Directly getting the exported `rfapi_core` from Render Fix's DLL (At your own risk)

Method '2' should be avoided as method '1' is significantly simpler and better supported. The option is only there for a potential rainy day, if it ever arrives.

"User-exported functions" sounds a lot more fancy than it is. So let's go through what they are and how you make them.

## User-Exported Functions
Render Fix is capable of calling a set of functions in your mod directly, these are called "user-exported functions". These functions are `RF_EarlyInit` & `RF_Init`, & both are called at different times during Render Fix's boot process:

- `RF_EarlyInit`
  - Called just before RF begins to init its own features, this makes it useful for controling RF or other time sensitive actions, such as replacing files that haven't been loaded yet. However, because RF isn't done booting, its use cases are limited.
- `RF_Init`
  - Called at the end of RF's boot process. Since RF is done booting, almost all of the API features are available. However, actions such as replacing files will have no effect at this stage, since all features are done loading.

If you are unsure which to use, you should use `RF_Init`.

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
RF_Init(const RFAPI_CORE* pApiCore, const char* path, const HelperFunctions& helperFunctions)
{
    // Ran after Render Fix has init'd features
    // Your code here
}

extern "C" __declspec(dllexport) // Mark as extern "C" and as exported
void
RF_EarlyInit(const RFAPI_CORE* pApiCore, const char* path, const HelperFunctions& helperFunctions)
{
    // Ran just before Render Fix starts to init features
    // Your code here
}
```

The examples marked each function individually as `extern "C"`, but placing them in a `extern "C"` block with `{` & `}` symbols would work the same.

So now you have the API, but there's a few more things you need to do before you're ready to use it.

## Using the API
Once you have the Core API pointer, you can access the other API modules through it. Before we can start using it though, there are a few extra steps to take.

### API Module Availability

It's important you check the availability of the API modules before getting them, as some are only available at certain times.

All the info of what's available when is written in the API header, and can be seen in the comment above API module structures. Here's quick a rundown:

```
RF_EarlyInit    : Control, Config, Renderstate, Shader, Font
RF_Init         : Config, Feature Check, Draw, Renderstate, Shader, Font
After Init      : Feature Check, Draw, Renderstate, Shader, Font
```

`RF_EarlyInit` refers to the user-exported function of the same name. API modules in this group can be called during this function.
`RF_Init` same as above ^ .
`After Init` refers to any time after Render Fix, and by extension all other mods, have finished booting entirely; in other words, when the user is in-game.

Always take the time to double check when a API module is available. Most of the time nothing will happen if you access one when it isn't available, but it's totally undefined and things could get serious very fast.

Now that you know when the module you're after is available, let's actually *use* it!

### Structure Versions

Some API modules and functions may only be available in later versions of Render Fix than the one the user has installed. In a perfect world, everyone would be running the latest version of everything; but that isn't the case and it needs to be accounted for. 

Luckily, it's easy! Each API module has a structure member called `version`; this is a number that increases whenever a new function is added to that API module. We can use this number to know what functions are currently available via large comments in the structures themselves.

So, first, we need to make sure the API module is available in the installed Render Fix version. In the header, it looks like:
```cpp
typedef struct // RFAPI_CORE example
{
    /****** Version >= 0 ************************************************************/
    uint32_t version;                           /* structure version                */

    /**** Mod version ****/
    RF_VERSION modver;                          /* current Render Fix version       */
...
    /****** Version >= 1 ************************************************************/
    const RFAPI_EXAMPLE*     pApiExample;       /* Example API                      */
...
```
This tells us that the 'Example' API requires version 1 of 'Core' or above. In your code, the check would look like:
```cpp
...
    if (pApiCore->version >= 1) // Core API 'version' check
    {
        const RFAPI_EXAMPLE* rf_example = pApiCore->pApiExample;

        ...
    }
...
```
If the user has an old version of Render Fix, this check will fail. That sounds bad, but the alternative is a crash because the module you're trying to access doesn't exist. Not working is *always* better than a crash.

If the API is vital to your mod though, now is the perfect time to throw a warning and let the user know they've made a mistake. Assuming all is good though, let's move onto the module itself.

Now we've got the API module, we need to do another version check for its individual functions. Luckily, the process is exactly the same:
```cpp
    ...
        const RFAPI_EXAMPLE* rf_example = pApiCore->pApiExample;

        /** Assume the function needs version 2 or higher **/

        if (rf_example->version >= 2) // RFAPI_EXAMPLE 'version' check
        {
            rf_example->func();
        }
    ...
```
Again, if the Render Fix version is old, this will stop anything bad from happening. It might seem clunky to do this every time, but it's very important and the API wouldn't be possible without it. Also remember that you can check functions in groups; if the user has version 2, then version 1 functions are also available.

But, checking each individually is a bit cumbersome. Very thorough, but cumbersome. Luckily, there is a faster way! It's a little heavy handed, but sometimes heavy handed is perfect for the job.

Instead of checking each module individually, you can instead do a blanket check on Render Fix's mod version. Render Fix defines a macro for this purpose, `RFD_CHECKVER`.

Using it is simple. It returns `true` if the current mod version is equal to or above the set version. For Example:
```cpp
...
    if ( RFD_CHECKVER(pApiCore, 1,2,1,0) )
    {
        // Use API here
    }
...
```
Is checking if the installed Render Fix version is above or equal to version `1.2.1`. It's much less precise than checking each structure version individually, and offers you less oportunity to compromise on older Render Fix versions. But what you lose in precision, you gain in speed.

Just be warned, you shouldn't just blindly set this to the latest Render Fix version. There *will* be users on older versions, and your mod will likely work exactly the same on these versions. So, take a second to use the lowest version number possible, so as many people can enjoy your mod as possible.

### That's It
And with that, you're done! You can now access every API module and function using those simple steps. There's some additional, complete examples below if you need them. Additional info and comments about each API and their functions can be found in the API header.

## Complete Examples
Checking each API structure version individually
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

Checking the Render Fix mod version
```cpp
extern "C" __declspec(dllexport)
void
RF_Init(const RFAPI_CORE* pApiCore, const char* path, const HelperFunctions& helperFunctions)
{
    /** Assume version requirements are the same as above, and Render Fix version
        1.3.2 is the minimum version for those requirements to be met **/

    if ( RFD_CHECKVER(pApiCore, 1,3,2,0) )
    {
        const RFAPI_EXAMPLE* rf_exam = pApiCore->pApiExample;

        rf_exam->func1(); // Needs version >= 1
        rf_exam->func2(); // Needs version >= 2
    }
    else
    {
        // Mod version too low, handle error
    }
}
```

Using API after Init:
```cpp
const RFAPI_EXAMPLE* ExampleApi;

const EXAMPLE_FUNC* ExampleApi_Func1;

void
FunctionThatRunsLater(int mode)
{
    if ( mode == CALL_FUNC2 )
    {
        ExampleApi->func2( argument ); // call from API pointer
    }
    else
    {
        ExampleApi_Func1( argument ); // call function pointer
    }
}

/** Render Fix Init **/

extern "C" __declspec(dllexport)
void
RF_Init(const RFAPI_CORE* pApiCore, const char* path, const HelperFunctions& helperFunctions)
{
    /** Assume version requirements are the same as above, and Render Fix version
        1.3.2 is the minimum version for those requirements to be met **/

    if ( RFD_CHECKVER(pApiCore, 1,3,2,0) )
    {
        const RFAPI_EXAMPLE* rf_exam = pApiCore->pApiExample;

        ExampleApi       = rf_exam;         // store API pointer
        ExampleApi_Func1 = rf_exam->func1;  // store individual function
    }
}
```

## Additional Notes

The API and its pointers are constant, you can store them in local variables and use them later rather than going through the entire API tree every time.

The API will never have breaking changes. Header names may change, but your old code will always continue work. Sometimes functions are depricated, but continued suppport of old mods is a top priority. At worst, a function will just do nothing past a point, but that is always a last resort when all else has failed.

The examples used a `const HelperFunctions&` for user-exported function parameters; this is exactly the same as a `const HelperFunctions*`, although they're accessed differently, the compiled code is actually exactly the same. If you prefer pointers, you can use them.

These examples were in C++, as that's most commonly used for modding, but it works the same in C. If you're using C, I'm sure you can figure out what you need to change on your own.
