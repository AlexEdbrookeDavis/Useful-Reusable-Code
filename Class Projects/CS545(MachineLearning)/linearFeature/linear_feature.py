print(__doc__)

import matplotlib
# Force matplotlib to not use any Xwindows backend.
matplotlib.use('Agg')

import numpy as np
import matplotlib.pyplot as plt
from itertools import cycle

import pandas as pd
from matplotlib.backends.backend_pdf import PdfPages
import csv

from sklearn import svm, datasets
from sklearn.metrics import roc_curve, auc, accuracy_score
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import label_binarize
from sklearn.multiclass import OneVsRestClassifier
from sklearn.svm import SVC
from scipy import interp
# Import some data to play with
#iris = datasets.load_iris()
#X = iris.data
#y = iris.target
url = 'X_train.csv'
X = pd.read_csv(url, header=None, index_col=57)
url = 'y_train.csv'
y =  np.loadtxt(fname = url, delimiter = ',').tolist()
url = 'X_test.csv'
X_test = pd.read_csv(url, header=None, index_col=57)
url = 'y_test.csv'
y_test =  np.loadtxt(fname = url, delimiter = ',').tolist()
# Learn to predict each class against the other

clf = SVC(kernel='linear')

clf.fit(X, y)

y_score = clf.fit(X, y).decision_function(X_test)

print (clf.coef_)


import operator
min_index, min_value = min(enumerate(abs(clf.coef_[0])), key=operator.itemgetter(1))
coef = clf.coef_[0].tolist()
print (coef[55])
print (sorted(range(len(coef)), key=lambda i: abs(coef[i]))[-5:])
print (accuracy_score(clf.predict(X_test), y_test))

for index in range(57, 2, -1):
	min_index, min_value = min(enumerate(map(abs, coef)), key=operator.itemgetter(1))
	coef.pop(min_index)
	#y.pop(min_index)
	#y_test.pop(min_index)
	X = X.drop(min_index, 1)
	X_test = X_test.drop(min_index, 1)
	X.columns = range(len(X.columns))
	X_test.columns = range(len(X_test.columns))

	clf = SVC(kernel='linear')
	clf.fit(X, y)
	y_score = clf.fit(X, y).decision_function(X_test)
	print (accuracy_score(clf.predict(X_train), y_train))
