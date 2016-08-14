from flask import Flask, render_template, request
import serial

app = Flask(__name__)
ser = serial.Serial("/dev/ttyACM0", 9600)

@app.route("/", methods=["GET"])
def unlock():
    if "code" in request.args:
        ser.write("move ")
        ser.write(str(request.args["code"]))
        ser.write("\r")
        ser.flush()
    return render_template("unlock.html")

@app.route("/change", methods=["GET"])
def change():
    if "old" in request.args and "new" in request.args:
        ser.write("change ")
        ser.write(str(request.args["old"]))
        ser.write(" ")
        ser.write(str(request.args["new"]))
        ser.write("\r")
        ser.flush()
    return render_template("change.html")

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080, debug=True)
