interface Something {
    penguin: number;
};

async function doSomething(): Promise<any> {
    // ...

    const response = await fetch("https://pingwin.com/api/v1/clone/abcdef");
    const json = await response.json();
    const something = json as Something;

    console.log(something.penguin);

    // ...
}