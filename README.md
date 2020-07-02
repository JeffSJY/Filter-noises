### Filtros & Ruidos
![filtros ruidos](https://user-images.githubusercontent.com/46036174/86392548-01c1e780-bc72-11ea-9686-a2ec67aa2ff8.png)


### Instalação OpenCV linux C++

* #### Passo 1 - Update

``` 
sudo apt-get update
```

``` 
sudo apt-get upgrade
```

* #### Passo 2 - Instalando Dependências
```
sudo apt install g++
```
```
sudo apt install build-essential
```
``` 
sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
```

``` 
sudo apt-get install libopencv-dev
```

* #### Passo 3 - Download OpenCv

``` 
sudo -s
```

``` 
cd /opt
```

``` 
git clone https://github.com/Itseez/opencv.git
```

``` 
git clone https://github.com/Itseez/opencv_contrib.git
```

* #### Passo 4 - Instalação OpenCV

 

``` 
 cd opencv
```

``` 
mkdir release
```

``` 
cd release
```

``` 
cmake -D BUILD_TIFF=ON -D WITH_CUDA=OFF -D ENABLE_AVX=OFF -D WITH_OPENGL=OFF -D WITH_OPENCL=OFF -D WITH_IPP=OFF -D WITH_TBB=ON -D BUILD_TBB=ON -D WITH_EIGEN=OFF -D WITH_V4L=OFF -D WITH_VTK=OFF -D BUILD_TESTS=OFF -D BUILD_PERF_TESTS=OFF -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib/modules /opt/opencv/
```

``` 
make -j4
```

``` 
make install
```

``` 
ldconfig
```

### Executar arquivo

``` 
g++ main.cpp -o output `pkg-config --cflags --libs opencv`
```

``` 
./output
```

### Filtros & Ruidos
* [Zoom](https://pt.wikipedia.org/wiki/Zoom_(efeito)) 
* [Gaussiano](https://en.wikipedia.org/wiki/Gaussian_filter) 
* [Prewitt](https://pt.wikipedia.org/wiki/Operador_Prewitt)
* [Sobel](https://pt.wikipedia.org/wiki/Filtro_Sobel)
* [Mediana](https://pt.wikipedia.org/wiki/Filtro_n%C3%A3o_linear)
* [Laplaciano](https://pt.wikipedia.org/wiki/Laplaciano)
* [Sal e Pimenta](https://prezi.com/xpzu0uq3rk4o/ruido-sal-e-pimenta-e-a-media-contra-harmonica/)