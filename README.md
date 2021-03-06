# cloth-simulations
cloth simulation using api,  OpenGL, C++

## My purpose 
**Implement a cloth simulation with elastic forces using OpenGL(C++).**

## My goal
**Implement elasticity and transparency, overlay between multi clothes.**
+ Simulate a cloth with elastic forces.

## My steps
Tasks have a lot of separated small tasks in [Issues](https://github.com/yamada-k-25/cloth-simulations/issues) and [Project Board](https://github.com/yamada-k-25/cloth-simulations/projects/1).

| Task | Description | Progress(%) | Deadline |
----  | --- | -----: | ----:
|1. Create a skelton codes |何も実装されていない描画コード| Completed| 1/31 |
|2. Draw a surface|面だけを表示するプログラム| 50% | 1/31 |
|3. Create a surface having cotorable points on its self||0| 2/15 |
|4. Create Cloth Class with Elastic Force| 3を用いて, 弾性力を持つ布クラスを作成する | 0 | 2/15 |
|5. Add Transparency to Cloth Class| 5を用いて, 光の透過性を布のクラスを作成する| 0| 2/15 |


## Issues
There are issues on [issues in this project]()

## Branch Configuration
master <-  feature

## Execute source file
以下のコマンドによって, source fileをコンパイルする
```
$ gcc -framework GLUT -framework OpenGL fileName
$ ./a.out
```
`Library/`以下のクラスを使っているソースをコンパイルする時はそれらを一緒にコンパイルする必要がある.
```
$ gcc -framework GLUT -framework OpenGL fileName1 Library/fileName2
$ ./a.out
```

## References
+ Elasticity Model: 
+ TransParency Model:
+ Collision Model:
