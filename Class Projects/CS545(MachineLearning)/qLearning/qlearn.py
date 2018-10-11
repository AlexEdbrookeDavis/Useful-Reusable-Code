print(__doc__)

import matplotlib
# Force matplotlib to not use any Xwindows backend.
matplotlib.use('Agg')

import math
from decimal import *

import numpy as np
import matplotlib.pyplot as plt
from itertools import cycle

import pandas as pd
from matplotlib.backends.backend_pdf import PdfPages
import csv

from random import randint



#init data
EPISODE_COUNT = 5000
ACTION_COUNT = 200
trainingreward = np.zeros(50)

#init Q array (5 state value dimensions, 5 action dimension)
Qarr = np.zeros((3, 3, 3, 3, 3, 5))

#greedy selection variable (multiplied by 100 for simplicity)
epsilon = 100


for i in range(0, EPISODE_COUNT):
	#init board (0 wall, 1 blank, 2 can)
	board = np.zeros((12, 12))
	for j in range(0, 10):
		for k in range(0, 10):
			board[j+1, k+1] = randint(1, 2)
	#init bot location (horizontal 0, vertical 1 from top left)
	botloc = np.zeros(2)
	botloc[0] = randint(1, 10)
	botloc[1] = randint(1, 10)

	episodereward = 0
	for j in range(0, ACTION_COUNT):
		#observestate (self, up, left, right, down)
		state = np.zeros(5)
		#self
		state[0] = board[int(botloc[0]), int(botloc[1])]
		state[1] = board[int(botloc[0]), int(botloc[1] - 1)]
		state[2] = board[int(botloc[0] - 1), int(botloc[1])]
		state[3] = board[int(botloc[0] + 1), int(botloc[1])]
		state[4] = board[int(botloc[0]), int(botloc[1] + 1)]
		#greedy action selection
		if (randint(0, 100) > epsilon):
			#do greedy
			randoma = np.random.choice(np.where(Qarr[int(state[0]), int(state[1]), int(state[2]), int(state[3]), int(state[4]), :] == Qarr[int(state[0]), int(state[1]), int(state[2]), int(state[3]), int(state[4]), :].max())[0])
		else:
			#do random action (0 can, 1 up, 2 left, 3 right, 4 down)
			randoma = randint(0, 4)
		#save qtable location
		oldq = np.zeros(6)
		oldq[0] = state[0]
		oldq[1] = state[1]
		oldq[2] = state[2]
		oldq[3] = state[3]
		oldq[4] = state[4]
		oldq[5] = randoma
		#take action get reward
			#can grab
		if(randoma == 0):
			#can grabbed
			if(state[0] == 2):
				#remove can
				board[int(botloc[0]), int(botloc[1])] = 1
				reward = 10
			#can not grabbed
			else:
				reward = -1
		#move up
		if(randoma == 1):
			#wall
			if(state[1] == 0):
				reward = -5
			#no wall
			else:
				botloc[1] = botloc[1] - 1
				reward = 0
		#move left
		if(randoma == 2):
			#wall
			if(state[2] == 0):
				reward = -5
			#no wall
			else:
				botloc[0] = botloc[0] - 1
				reward = 0
		#move right
		if(randoma == 3):
			#wall
			if(state[3] == 0):
				reward = -5
			#no wall
			else:
				botloc[0] = botloc[0] + 1
				reward = 0
		#move down
		if(randoma == 4):
			#wall
			if(state[4] == 0):
				reward = -5
			#no wall
			else:
				botloc[1] = botloc[1] + 1
				reward = 0
		#print "movement data"
		#print state
		#print randoma
		#updatestate
		state = np.zeros(5)
		#self
		state[0] = board[int(botloc[0]), int(botloc[1])]
		state[1] = board[int(botloc[0]), int(botloc[1] - 1)]
		state[2] = board[int(botloc[0] - 1), int(botloc[1])]
		state[3] = board[int(botloc[0] + 1), int(botloc[1])]
		state[4] = board[int(botloc[0]), int(botloc[1] + 1)]
		#calculate best Qtable action value in new state
		maxq = Qarr[int(state[0]),int(state[1]),int(state[2]),int(state[3]),int(state[4]),:].max()
		#update Q table
		#if(oldq[0] == 1 and Qarr[int(oldq[0]), int(oldq[1]), int(oldq[2]), int(oldq[3]), int(oldq[4]), 0] == Qarr[int(oldq[0]), int(oldq[1]), int(oldq[2]), int(oldq[3]), int(oldq[4]), :].max()):
		#	print "ERROR"
		Qarr[int(oldq[0]), int(oldq[1]), int(oldq[2]), int(oldq[3]), int(oldq[4]), int(oldq[5])] = Qarr[int(oldq[0]), int(oldq[1]), int(oldq[2]), int(oldq[3]), int(oldq[4]), int(oldq[5])] + 0.2 * (reward + 0.5 * maxq - Qarr[int(oldq[0]), int(oldq[1]), int(oldq[2]), int(oldq[3]), int(oldq[4]), int(oldq[5])])
		episodereward = episodereward + reward
	#decrement epsilon
	if(i % 50 == 49 and epsilon > 10):
		epsilon = epsilon - 1
	if(i % 100 == 99 ):
		trainingreward[(int(i / 100))] = int(episodereward)
#save Training reward data
#trainingreward.to_csv('TrainReward.csv')
np.savetxt('TrainReward.csv', trainingreward, delimiter=',')
Qold = Qarr
#Test runs
testrewards = np.zeros(EPISODE_COUNT)
for i in range(0, EPISODE_COUNT):
	#init board (0 wall, 1 blank, 2 can)
	board = np.zeros((12, 12))
	for j in range(0, 10):
		for k in range(0, 10):
			board[j+1, k+1] = randint(1, 2)
	#init bot location (horizontal 0, vertical 1 from top left)
	botloc = np.zeros(2)
	botloc[0] = randint(1, 10)
	botloc[1] = randint(1, 10)

	episodereward = 0
	for j in range(0, ACTION_COUNT):
		#observestate (self, up, left, right, down)
		state = np.zeros(5)
		#self
		state[0] = board[int(botloc[0]), int(botloc[1])]
		state[1] = board[int(botloc[0]), int(botloc[1] - 1)]
		state[2] = board[int(botloc[0] - 1), int(botloc[1])]
		state[3] = board[int(botloc[0] + 1), int(botloc[1])]
		state[4] = board[int(botloc[0]), int(botloc[1] + 1)]
		#greedy action selection
		randoma = np.random.choice(np.where(Qarr[int(state[0]), int(state[1]), int(state[2]), int(state[3]), int(state[4]), :] == Qarr[int(state[0]), int(state[1]), int(state[2]), int(state[3]), int(state[4]), :].max())[0])
		#save qtable location
		oldq = np.zeros(6)
		oldq[0] = state[0]
		oldq[1] = state[1]
		oldq[2] = state[2]
		oldq[3] = state[3]
		oldq[4] = state[4]
		oldq[5] = randoma
		#take action get reward
			#can grab
		if(randoma == 0):
			#can grabbed
			if(state[0] == 2):
				#remove can
				board[int(botloc[0]), int(botloc[1])] = 1
				reward = 10
			#can not grabbed
			else:
				reward = -1
		#move up
		elif(randoma == 1):
			#wall
			if(state[1] == 0):
				reward = -5
			#no wall
			else:
				botloc[1] = botloc[1] - 1
				reward = 0
		#move left
		elif(randoma == 2):
			#wall
			if(state[2] == 0):
				reward = -5
			#no wall
			else:
				botloc[0] = botloc[0] - 1
				reward = 0
		#move right
		elif(randoma == 3):
			#wall
			if(state[3] == 0):
				reward = -5
			#no wall
			else:
				botloc[0] = botloc[0] + 1
				reward = 0
		#move down
		elif(randoma == 4):
			#wall
			if(state[4] == 0):
				reward = -5
			#no wall
			else:
				botloc[1] = botloc[1] + 1
				reward = 0
		else:
			print("ERROR")
		#print "movement data"
		#print state
		#print randoma
		#updatestate
		state = np.zeros(5)
		#self
		state[0] = board[int(botloc[0]), int(botloc[1])]
		state[1] = board[int(botloc[0]), int(botloc[1] - 1)]
		state[2] = board[int(botloc[0] - 1), int(botloc[1])]
		state[3] = board[int(botloc[0] + 1), int(botloc[1])]
		state[4] = board[int(botloc[0]), int(botloc[1] + 1)]
		#maxq = max(Qarr[int(state[0]),int(state[1]),int(state[2]),int(state[3]),int(state[4]),:])
		#update Q table
		#Qarr[int(oldq[0]), int(oldq[1]), int(oldq[2]), int(oldq[3]), int(oldq[4]), int(oldq[5])] = Qarr[int(oldq[0]), int(oldq[1]), int(oldq[2]), int(oldq[3]), int(oldq[4]), int(oldq[5])] + 0.01 * (reward + 0.9 * maxq - Qarr[int(oldq[0]), int(oldq[1]), int(oldq[2]), int(oldq[3]), int(oldq[4]), int(oldq[5])])	
		episodereward = episodereward + reward
	testrewards[i] = episodereward

print(np.mean(testrewards))
print(np.std(testrewards))
