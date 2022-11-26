一个超过deflate的压缩算法

An algorithm beyond deflate

使用devc++5.11打开devfile\dawn.dev，即可编辑项目

Open devfile\dawn.dev with devc++5.11 to edit the project

编译后输入：dawn infile infile2 ... -c outfile -rall -w32768 即可压缩文件（或文件夹）

After compiling, enter: dawn infile infile2... - c outfile - rall - w32768 to compress the file (or folder)

如果只需要将文件打包，则输入dawn infile infile2 ... -bc outfile此时不对文件进行任何压缩操作

If you only need to package the file, enter dawn infile infile2... - bc outfile. At this time, the file will not be compressed

主要使用dawn算法压缩（自己写出的压缩率超越deflate的算法）

Mainly use the Dawn algorithm for compression (the compression rate written by myself exceeds the deflate algorithm)

也有使用lzw、huffman、rlc算法的压缩

There are also compression algorithms using lzw, huffman, and rlc

其中lzw和rlc经过优化，使用优化过的lzw和rlc压缩后的文件比传统lzw、rlc压缩的文件要小

Among them, lzw and rlc are optimized, and the files compressed with optimized lzw and rlc are smaller than those compressed with traditional lzw and rlc

如需加密，则在原命令后添加："-p你自己的密码" （注意：加密算法是我自己写出做测试用的，不能确保一定安全）

If encryption is required, add "-p your own password" after the original command (note: I wrote the encryption algorithm for testing, which cannot ensure certain security)

本软件未经过速度上的优化，所以压缩过程可能较慢

The software is not optimized in speed, so the compression process may be slow

注意：dawn算法、打包算法、加密算法和输出文件的格式都是本人自创，所以其他软件不支持。

Note: Dawn algorithm, packaging algorithm, encryption algorithm and output file format are all created by myself, so other software does not support them.
