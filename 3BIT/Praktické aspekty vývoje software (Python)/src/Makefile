#
# Project:	Calculator
#
# File: 	Makefile
# Subject:	IVS
#
# Authors:	Jakub Kováčik		xkovac58
#			Roman Marek			xmarek74
#			Jakub Potoček		xpotoc07
#			Vladislav Mikheda	xmikhe00
#

REQUIREMENTS = requirements.txt
PIP = venv/bin/pip
PYTHON = venv/bin/python3
CALCULATOR = gui.py
PROFILING = profiling.py
PROFILING_DATA = ../profiling/profilerNumbers.txt
TEST_FILE=$(wildcard *_tests.py)
TEAM = xkovac58_xmarek74_xpotoc07_xmikhe00

all: init run
pack:
	doxygen Doxyfile
	mkdir -p ../../$(TEAM)/repo
	cp -rf ../install ../../$(TEAM)
	cp -rf ../doc ../../$(TEAM)
	cp -rf ../.  ../../$(TEAM)/repo
	cd ../../$(TEAM)/repo && rm -rf doc install src/output src/venv src/__pycache__ src/varovani_doxygenu.txt src/xkovac58_xmarek74_xpotoc07_xmikhe00.zip
	cd ../../ && zip -r $(TEAM).zip $(TEAM)
	mv ../../$(TEAM).zip ./
	rm -rf ../../$(TEAM)
clean:
	rm -rf venv __pycache__ ../doc varovani_doxygenu.txt  xkovac58_xmarek74_xpotoc07_xmikhe00.zip output
test:
	$(PYTHON) $(TEST_FILE)
doc:
	doxygen Doxyfile
run:
	$(PYTHON) $(CALCULATOR)
profile:
	$(PYTHON) $(PROFILING) < $(PROFILING_DATA)
init: $(REQUIREMENTS)
	python3 -m venv venv
	$(PYTHON) -m pip install --upgrade pip
	$(PIP) install -r $(REQUIREMENTS)
pyinstall:
	sudo apt update
	sudo apt install python3
	sudo apt install python3-pip
	sudo apt install python3-venv
