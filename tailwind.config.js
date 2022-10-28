/** @type {import('tailwindcss').Config} */
module.exports = {
  content: ["./dist/*.html", "./src/**/*.{js,jsx,ts,tsx}"],

  theme: {
    extend: {
      keyframes: {
        arrows: {
          "0%": { transform: "translateX(0em)" },
          "50%": { transform: "translateX(1em)" },
          "100%": { transform: "translateX(0em)" },
        },
      },
      animation: {
        arrows_animation: "arrows 2s cubic-bezier(0.4, 0, 0.6, 1) infinite",
      },
    },
  },
  plugins: [],
};
