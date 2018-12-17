Neural Net
==========
Implementation of a neural network in C++.

Authors
-------
	Leonn Paiva	 <master>

USAGE
-------

No empty lines on Training  & test files

	- Training Only
		`./neuralNet <Training Data File> <minimum error> <max epochs> <Data Output File> <Global Data Output File>`
	- Training & Test
		`./neuralNet <Training Data File> <minimum error> <max epochs> <Data Output File> <Global Data Output File> -t <Test Data Output File>`
	- Training & Test from File
		`./neuralNet <Training Data File> <minimum error> <max epochs> <Data Output File> <Global Data Output File> -tf <Test Data Input File> <Test Data Output File>`
	- Generating Trainig data  (XOR) in data/xor
		`./data/xor/xor "number of inputs for training" > "Training Data File"`
	- Result test analysis
		`./data/test_analysis/test_analysis <Test Data Output File>`

TODO
----------
- [x] Sigmoid transfer function
- [x] Gaussian transfer function
- [x] Pendigits test
- [ ] Export network weights
- [ ] Import network weights
- [x] Result test analysis

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

