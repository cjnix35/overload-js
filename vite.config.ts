import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [react()],

  publicDir: false,
  base: "", // embedded deployment,
  server: {
    open: "/src/frontend/index.html",
    port: 8080,
  },

  build: {
    outDir: "./dist",
    emptyOutDir: true,
    rollupOptions: {
      input: {
        html: "index.html",
      },

      output: {
        assetFileNames: "assets/[hash][extname]",
        chunkFileNames: "assets/[hash].js",
        entryFileNames: "assets/[hash].js",
      },
    },
  },
});
