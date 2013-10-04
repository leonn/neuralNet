Neural Net
==========
Implementation of a neural network in C++.

Authors
-------
	Leonn Paiva	 <master>

USAGE
-------
	- Trainning Only
		./neuralNet <Training Data File> <minimum error> <max epochs> <Data Output File> <Global Data Output File>
	- Trainning & Test
		./neuralNet <Training Data File> <minimum error> <max epochs> <Data Output File> <Global Data Output File> -t <Test Data Output File>
	- Trainning & Test from File
		./neuralNet <Training Data File> <minimum error> <max epochs> <Data Output File> <Global Data Output File> -tf <Test Data Input File> <Test Data Output File>
	- Generating Trainig data  (XOR) in data/xor
		- ./xor "number of inputs for training" > "Training Data File"

TODO
-------
	- Sigmoid transfer function
	- Gaussian transfer function
	- pendigits test


Changelog:
----------
	- 0.1 -
		- First version
	- 0.2 -
		- simple implamentation done
	- 0.3 -
		- support for training data files
	- 0.4 -
		- improvement on algorithm
	- 0.5 -
		- ...

---------

