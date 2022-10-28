const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const path = require("path");

let mode = "development";
let devtool = null;
if (process.env.NODE_ENV === "production") {
  mode = "production";
  devtool = "eval-source-map";
}

const plugins = [
  new MiniCssExtractPlugin(),
  new HtmlWebpackPlugin({
    template: "./src/frontend/index.html",
  }),
];

let target = "web";

module.exports = {
  mode: mode,
  target: target,
  plugins: plugins,

  devtool: devtool,
  entry: {
    index: path.resolve(__dirname, "src/frontend/index.js"),
  },

  output: {
    assetModuleFilename: "assets/[hash][ext][query]",
    clean: true,
  },

  module: {
    rules: [
      {
        test: /\.(png|jpe?g|gif|txt|svg)$/i,
        type: "asset",

        /**
         * If you want to inline larger images, you can set
         * a custom `maxSize` for inline:
         */
        parser: {
          dataUrlCondition: {
            maxSize: 4 * 1024,
          },
        },
      },

      {
        //if issuer is jsx/tsx then we use SVGR loader https://react-svgr.com/
        test: /\.svg$/i,
        issuer: /\.[jt]sx?$/,

        use: ["babel-loader", "@svgr/webpack"],
      },

      {
        test: /\.(s[ac]|c)ss$/i,
        use: [
          {
            loader: MiniCssExtractPlugin.loader,
            options: {
              publicPath: "",
            },
          },
          "css-loader",
          "postcss-loader",
          "sass-loader",
        ],
      },
      {
        test: /\.jsx?$/,
        exclude: /node_modules/,
        use: {
          loader: "babel-loader",
          options: {
            /**
             * From the docs: When set, the given directory will be used
             * to cache the results of the loader. Future webpack builds
             * will attempt to read from the cache to avoid needing to run
             * the potentially expensive Babel recompilation process on each run.
             */
            cacheDirectory: true,
          },
        },
      },
    ],
  },

  resolve: {
    extensions: [".js", ".jsx"],
  },
};
