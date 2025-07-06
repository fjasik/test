# For the interviewers

This provides optional follow-up questions, talking points, and example solutions for each section of the technical test.

## 0. General cyber security

We want to hear (more or less):

- Reconnaissance
- Phishing
- Social engineering
- Weak/reused passwords
- Public infrastructure (DNS, website, services)
- Unpatched systems
- Targeting employees
- etc...

If stuck, ask something like:

- "What would you look for about the company online?"
- "Would you start by targeting people or systems?"
- "What kind of weak points do you think small companies have?"
- "What would a phishing email look like?"

## 1. JS/TS 

Obviously the fetch and json can throw and that has to be handled.

Add one small fix task in TS:
    
- For example: "Refactor the TS function to enforce runtime validation of json before accessing `.penguin`."

```ts
    interface Something {
        penguin: number;
    }

    function isSomething(data: any): data is Something {
        return (
            typeof data === "object" &&
            data !== null &&
            typeof data.penguin === "number"
        );
    }

    async function fetchData(): Promise<void> {
        let response: Response;

        try {
            response = await fetch("https://pingwin.com/api/v1/clone/abcdef");
        } catch (err) {
            console.error("Network error during fetch:", err);
            return;
        }

        let json: unknown;

        try {
            json = await response.json();
        } catch (err) {
            console.error("Failed to parse JSON:", err);
            return;
        }

        if (!isSomething(json)) {
            console.error("Invalid response format:", json);
            return;
        }

        console.log(json.penguin);
    }
```

## 2. C++ Scope Exit

"We repeat cleanup code all over. Can you design a helper to run cleanup code automatically when leaving scope?".

Goal: allow syntax like:

```cpp
    OnScopeExit(WinHttpCloseHandle(session););
```

Example implementation:

```cpp
    #include <functional>

    class ScopeExit {
    public:
        // explicit keyword prevents implicit conversions when constructing an object from a single-argument constructor.
        explicit ScopeExit(std::function<void()> fn)
            : m_fn(std::move(fn))
        {}

        ~ScopeExit() {
            m_fn();
        }

        // Disable copy and move
        ScopeExit(const ScopeExit&) = delete;
        ScopeExit& operator=(const ScopeExit&) = delete;
        ScopeExit(ScopeExit&&) = delete;
        ScopeExit& operator=(ScopeExit&&) = delete;

    private:
        std::function<void()> m_fn;
    };
```

Now no matter where you return, the destructors handle cleanup. Example usage:

```cpp
    HINTERNET session = WinHttpOpen(...);
    if (!session) return false;

    ScopeExit cleanupSession([&]() {
        WinHttpCloseHandle(session);
    });
```

Macros to further condense the notation

```cpp
    #define TOKENPASTE(x, y) x ## y
    #define TOKENPASTE2(x, y) TOKENPASTE(x, y)
    #define OnScopeExit(code) \
        auto TOKENPASTE2(scope_exit_, __LINE__) = ScopeExit([&]() { code; })

    // Expands to:
    // auto scope_exit_42 = ScopeExit([&]() { CloseHandle(h); });
    // Usage:
    // OnScopeExit(WinHttpCloseHandle(session););
```

## 3. Classic

Example answers mention:

- Writing outside the bounds of a memory buffer.
- Potential causes: unsafe functions (`strcpy`, `gets`, etc.).
- Consequences: memory corruption, crashes, code execution.
- Historical relevance: stack smashing, exploit vectors.

Can follow-up with:

- "How would you prevent one in C/C++?" or
- "Can this happen in modern languages like Rust or JS?"