const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const path = require("path");

let mode = "development";
if (process.env.NODE_ENV === "production") {
  mode = "production";
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

  devtool: "source-map",
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
        test: /\.(png|jpe?g|gif|txt)$/i,
        type: "asset",
        // generator: {emit: false}
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
        test: /\.svg(\?v=\d+\.\d+\.\d+)?$/,
        issuer: /\.[jt]sx?$/,
        use: ["babel-loader", "@svgr/webpack"],
        type: "asset",
      },
      {
        //else: just svg asset
        test: /\.svg(\?v=\d+\.\d+\.\d+)?$/,
        type: "asset",
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
