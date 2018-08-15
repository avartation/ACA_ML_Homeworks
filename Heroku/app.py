from flask import Flask
from flask import request
import pickle
import numpy as np

app = Flask(__name__)

@app.route('/')
def start():
    return """
    <h1>Type something like this:</h1>
    <h2>/predict?full_sq=60&floor=3&max_floor=9&build_year=1990&num_room=3&sub_area=Nizhegorodskoe</h2>
    """

@app.route('/predict')
def predict():
    """
    full_sq, floor, max_floor, build_year, num_room, sub_area
    
    """
    full_sq = request.args.get('full_sq')
    floor = request.args.get('floor')
    max_floor = request.args.get('max_floor')
    build_year = request.args.get('build_year')
    num_room = request.args.get('num_room')
    area = request.args.get('sub_area')
    
    area_file = open('sub_areas', 'rb')
    area_arr = pickle.load(area_file)
    area_file.close()
    
    area_one_hot = np.zeros((1, area_arr.shape[0]))
    i = np.where(area_arr==area)
    area_one_hot[0, i] = 1
    params = np.array([[full_sq, floor, max_floor, build_year, num_room]])
    params = np.column_stack((params, area_one_hot))
    
    model_file = open('model', 'rb')
    model = pickle.load(model_file)
    model_file.close()
    
    price = model.predict(params)
    return '<h1>House price: {}</h1>'.format(price[0])


import os

if __name__ == "__main__":
    port = int(os.environ["PORT"])
    app.run(port=port, host='0.0.0.0')

