print(__doc__)

import matplotlib
# Force matplotlib to not use any Xwindows backend.
matplotlib.use('Agg')

import numpy as np
import matplotlib.pyplot as plt

import pandas as pd
from matplotlib.backends.backend_pdf import PdfPages

from sklearn import svm, datasets
from sklearn.metrics import roc_curve, auc
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import label_binarize
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score
from sklearn.metrics import precision_recall_curve
from sklearn.metrics import average_precision_score
from sklearn.metrics import confusion_matrix
from scipy import interp

#init data
url = 'X_train2.csv'
X = np.genfromtxt(fname = url, delimiter = ',').tolist()
url = 'X_test2.csv'
X_test = np.genfromtxt(fname = url, delimiter = ',').tolist()
X = np.array(X)
X_test = np.array(X_test)

#train Regress and run on test data
clf = LogisticRegression(solver='liblinear', max_iter=100, random_state=None)
clf.fit(X[1:,1:], X[1:,0])

#score it
y_score = clf.fit(X[1:,1:], X[1:,0]).decision_function(X_test[1:,1:])

#accuracy, precision, recall, and confusion generators
fpr, tpr, threshold = roc_curve(X_test[1:,0], y_score)
roc_auc = auc(fpr, tpr)
print confusion_matrix(X_test[1:,0], clf.predict(X_test[1:,1:]))
print accuracy_score(clf.predict(X_test[1:,1:]), X_test[1:,0])
precision, recall, _ = precision_recall_curve(X_test[1:,0], y_score)
average_precision = average_precision_score(X_test[1:,0], y_score)

#graph printing
pp = PdfPages('test.pdf')

plt.figure()
lw = 2
plt.plot(fpr, tpr, color='darkorange',
         lw=lw, label='ROC curve (area = %0.2f)' % roc_auc)
plt.plot([0, 1], [0, 1], color='navy', lw=lw, linestyle='--')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('Receiver operating characteristic')
plt.legend(loc="lower right")
pp.savefig()
plt.clf()
plt.plot(recall, precision, lw=lw, color='navy',
         label='Precision-Recall curve')
plt.xlabel('Recall')
plt.ylabel('Precision')
plt.ylim([0.0, 1.05])
plt.xlim([0.0, 1.0])
plt.title('Precision-Recall: AUC={0:0.2f}'.format(average_precision))
plt.legend(loc="lower left")
pp.savefig()
pp.close()
