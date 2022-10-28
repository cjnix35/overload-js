const os = require("os");
const { exec } = require("child_process");

WINDOWS_COMMAND = "npm run build-dev && cd build\\Release && preview.exe";
UNIX_COMMAND = "npm run build-dev && cd build/ && ./preview ";

const watch = () => {
  exec("npm run watch", (error, stdout, stderr) => {
    if (error) {
      console.log(`BUILD ERROR: ${error.message}`);
    }
    if (stderr) {
      console.log(`STDERR: ${stderr}`);
      return;
    }
    console.log(`STDOUT: ${stdout}`);
  });
};

switch (os.platform()) {
  case "linux" || "darwin":
    exec(UNIX_COMMAND, (error, stdout, stderr) => {
      if (error) {
        console.log(`BUILD ERROR: ${error.message}`);
      }
      if (stderr) {
        console.log(`STDERR: ${stderr}`);
        return;
      }
      console.log(`STDOUT: ${stdout}`);
    });
    console.log("DEV BUILD SUCCESSFULL");
    watch();
    break;

  case "win32":
    exec(WINDOWS_COMMAND, (error, stdout, stderr) => {
      if (error) {
        console.log(`BUILD ERROR: ${error.message}`);
      }
      if (stderr) {
        console.log(`STDERR: ${stderr}`);
        return;
      }
      console.log(`STDOUT: ${stdout}`);
    });
    console.log("DEV BUILD SUCCESSFULL");
    watch();
    break;
}
