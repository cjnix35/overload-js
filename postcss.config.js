const autoprefixer = require("autoprefixer");
const tailwindcss = require("tailwindcss");
module.exports = {
  plugins: [
    "postcss-preset-env",
    tailwindcss("./tailwind.config.js"),
    autoprefixer,
  ],
};
