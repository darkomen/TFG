# Import all libraries needed for the tutorial

# General syntax to import specific functions in a library: 
##from (library) import (specific library function)
from pandas import DataFrame, read_csv

# General syntax to import a library but no functions: 
##import (library) as (give the library a nickname/alias)
import matplotlib.pyplot as plt
import pandas as pd #this is how I usually import pandas
import sys #only needed to determine Python version number

# Enable inline plotting
#%matplotlib inline

Location = r'C:\BQ.CSV'
df = pd.read_csv(Location)

# Create graph
df['Diametro X'].plot()

# Maximum value in the data set
MaxValue = df['Diametro X'].max()

# Text to display on graph
Text = str(MaxValue)

# Add text to graph
plt.annotate(Text, xy=(1, MaxValue), xytext=(8, 0), 
                 xycoords=('axes fraction', 'data'), textcoords='offset points')

#rint "The most popular name"
df[df['Diametro X'] == df['Diametro X'].max()]
#Sorted.head(1) can also be used

plt.show()