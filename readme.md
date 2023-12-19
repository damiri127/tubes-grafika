<h1>Gerhana Matahari</h1>

<p>Pake <a href="http://freeglut.sourceforge.net/">GLUT</a></p>

<p>
<s><u>main_glut.cpp</u> -- Ngeimpor "glut.h", ada fungsi yang kaga work, mending pake:</s> <br>
<u>main.cpp</u> -- Ngeimpor "freeglut.h"
</p>

<h2>Compile & Run</h2>
<p>Compile: </p>
<pre>
<s>g++ -o main_glut main_glut.cpp -lopengl32 -lglu32 -lglut</s>
g++ -o main main.cpp -lopengl32 -lglu32 -lfreeglut
</pre>
<p>Run: </p>
<pre>
./main.exe
</pre>

<p>Kalo di Visual Studio? You tell me :p</p>