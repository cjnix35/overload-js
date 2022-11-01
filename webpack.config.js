const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const ReactRefreshWebpackPlugin = require("@pmmmwh/react-refresh-webpack-plugin");
const path = require("path");

let mode = "development";
let devtool = "source-map";
let target = "web";

const plugins = [
  new MiniCssExtractPlugin(),
  new HtmlWebpackPlugin({
    template: "./src/frontend/index.html",
  }),
];

if (process.env.NODE_ENV === "production") {
  mode = "production";
  devtool = undefined;
}
if (process.env.SERVE) {
  plugins.push(new ReactRefreshWebpackPlugin());
}

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
            plugins: [
              process.env.SERVE && require.resolve("react-refresh/babel"),
            ].filter(Boolean),

            cacheDirectory: true,
          },
        },
      },
    ],
  },

  devServer: {
    hot: true,
  },
  resolve: {
    extensions: [".js", ".jsx"],
  },
};
