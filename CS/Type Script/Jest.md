By Facebook. Used for testing node projects.
To install jest and make it work with typescript, we need several packages:
```bash
npm install --save-dev jest @types/jest ts-jest @types/supertest supertest
```
`supertest` is used for testing Express APIs, great for integration testing. 
`@types/supertest` defines types for `supertest` and makes it compatible with typescript
`ts-jest` is a preprocessor that intercepts requests to the compiler, compiles the tests on the fly in memory and feeds them directly into node for execution.

We need to create and configure `jest.config.js` at the root dir of the project.
We also need to add jest to compiler options inside `tsconfig.json` 
Lastly, add `jest` run commands to `package.json` so node knows how to run 

# Using global variables with jest in ESM
Global variables are helpful to share a variable across multiple test files, suites, and cases. 
However, I encountered an error when attempting to add variables to the global namespace. The compiler kept complaining that the `globalThis` module didn't have an index signature, so it wouldn't accept something like this:
```ts
globalThis.MOCK_USER = {
  email: 'test@example.com',
  password: 'password123'
};
```

It turns out, we set the compiler's type safety feature to strict mode via `"strict": true` in the `tsconfig.ts` file
This requires that we define the type of the key-value pairs before we can insert them.
Consequently, we needed to use [[Declaration Merging]] to add these types to the `global` namespace.
In other words, we build on the namespace and define our own variables:
```ts
declare global {
    var MOCK_USER: { email: string; password: string };
    var MOCK_TOKEN: string;
    var mockLogger: jest.Mock;
}
```
This is the only syntax that worked for me.

We can set the values as such:
```ts
globalThis.MOCK_USER = {
  email: 'test@example.com',
  password: 'password123'
};
```

And we can use them in our test files by accessing them like `MOCK_USER.email`, for example

```ts
  it('should login the user', async () => {
    const res = await request(app)
      .post('/api/v1/login')
      .send({ email: MOCK_USER.email, password: MOCK_USER.password });
    expect(res.status).toBe(200);
    expect(res.body.token).toBeDefined();
  });
```
