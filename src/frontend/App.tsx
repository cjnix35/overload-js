import React from "react";
import Logo from "./components/Logo";

const App = () => {
  return (
    <div className="flex flex-col items-center justify-center text-center h-screen">
      <div className="flex flex-row-reverse items-center">
        <h1 className="mb-8 font-medium text-6xl ml-8 cursor-pointer hover:text-zinc-600 transition ease-in delay-150">
          <a href="https://github.com/cjnix35/overload-js" target={"_blank"}>
            OVERLOAD.JS
          </a>
        </h1>
        <div className="mb-8">
          <Logo />
        </div>
      </div>
    </div>
  );
};

export default App;
