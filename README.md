# k-medoids
Implementation of k-medoids algorithm in C programming language
## Example of usage
Cloning project and changing current directory:
```
git clone https://github.com/KlimentLagrangiewicz/k-medoids
cd k-medoids
```
Building from source (Linux):
```
make
```
Building from source (Windows):
```
make windows
```
If building was ok, you can find executable file in `bin` subdirectory.  
Run the program:
```
./bin/k-medoids ./datasets/iris/data.txt 150 4 3 ./datasets/iris/new_result.txt ./datasets/iris/res.txt

```