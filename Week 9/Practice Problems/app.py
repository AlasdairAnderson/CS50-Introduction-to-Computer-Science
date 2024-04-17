from flask import Flask, render_template, request

colors = [
    "red",
    "blue"
]

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        return render_template("index.html")
    else:
        print("Form submitted!")
        color = request.form.get("color")
        if color not in colors:
            print("{color} not in colors list".format(color=color))
            return render_template("index.html", alert = "Choose a Valid Color")

        return render_template("color.html", color=color)
