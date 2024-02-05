The dash framework allows you to create interactive web application very easily without much web knowledge. It's used by data scientists for many applications. So naturally, it's available for Python, but not for Java or C++ as of this writing.

Basically, a Dash web app is made from two parts. The layout, and callback functions. There are 4 steps to creating a simple application.
1. Initiate the app.
```python
from dash import Dash, dcc, html, Input, Output, dash_table as dt  
import dash_leaflet as dl  
import pandas as pd

app = Dash('Web App')
```

2. Define the HTML layout of the app. This is done via the `html` module, which handles simple html elements like `H1`, `Div`, `Img`.. and the `dcc` (Dash Core Components) module which handles the more complex components such as `Dropdown`, `Graph`...
```python
# From CS340 Project 2
app.layout = html.Div([
	# Image. But for some reason, this does not work and the image must be encoded. See https://community.plotly.com/t/adding-local-image/4896/17 for work around.
    html.Img(src="", style={'display': 'block', 'text-align': 'center', 'margin': 'auto'}),
    # Header
    html.H1("Project 2 by Afshin E. Ahvazi", style={'text-align': 'center'}), 
    # Line break 
    html.Br(),
    html.Div("Select Query Category"),  
    # Dropdowm menu. We can assign the elements an id to track changes to their values using the callback functions.
    dcc.Dropdown(  
        id="query-dropdown",  
        options=[  
            {'label': 'Water Rescue', 'value': 'Water'},  
            {'label': 'Mountain or Wilderness Rescue', 'value': 'Mountain'},  
            {'label': 'Disaster Rescue', 'value': 'Disaster'},  
            {'label': 'Reset', 'value': 'Reset'}  
        ]  
    ),  
    html.Br(),  
    # A datatable
    dt.DataTable(  
        id="datatable",  
        # The table data must be a dictionary. df is a pandas data frame.
        data=df.to_dict('records'),
        # The column names must match the data frame column names
        columns=[{"name": i, "id": i} for i in df.columns],  
        # Enable sorting data in the columns
        sort_action="native",  
        sort_mode="multi",
        # Enable searching and filtering data
        filter_action="native",  
        # Limit the number of rows in each table row  
        page_size=15  
    ),  
    # Vertical line that divides the page
    html.Hr(),  
    html.H2("Location of Dogs", style={'text-align': 'center'}),  
    html.Div(  
        id='geo-map'  
    )
])
```

3. Next, we have the callback functions. We want the application to react when the user interacts with it. Callback functions can keep track of data in html elements of the app, and respond appropriately everytime there are changes to those elements.
```python
@app.callback(
	# What element the output goes to
    Output(component_id='geo-map', component_property="children"), 
    # What triggers the function to be called.
    Input(component_id='datatable', component_property="data") 
def update_element(data):
	
)
```