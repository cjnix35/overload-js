import capybara from "../assets/images/capybara.png";
import "../styles/style.css";

const App = () => {
  return (
    <>
      <h1 className="text-white font-black bg-gray-500">React and C++</h1>

      <img src={capybara} alt="capybara" />
    </>
  );
};

export default App;
