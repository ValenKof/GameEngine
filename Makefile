release: folder
	cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make -j 2

debug: folder
	cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug && make -j 2

folder:
	mkdir -p build

clean:
	rm -rf build
