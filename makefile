all: RDAnalysis

RDAnalysis: Inversion.cxx Rejection.cxx RandomExtraction.cxx
	g++ `root-config --libs` -lMinuit `root-config --cflags` --std=c++11 -g \
		RandomExtraction.cxx -o RandomExtraction