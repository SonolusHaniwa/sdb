const char* vshaderSource = R"(
#version 430

layout (location=0) in vec3 pos;
out vec2 nxtpos;

uniform vec4 bg_color;
uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 proj_matrix;
layout (binding=0) uniform sampler2D samp;

void main(void) {	
	// vec4 lb = vec4(m_matrix[0][0], m_matrix[1][0], m_matrix[2][0], m_matrix[3][0]);
	// vec4 lt = vec4(m_matrix[0][1], m_matrix[1][1], m_matrix[2][1], m_matrix[3][1]);
	// vec4 rt = vec4(m_matrix[0][2], m_matrix[1][2], m_matrix[2][2], m_matrix[3][2]);
	// vec4 rb = vec4(m_matrix[0][3], m_matrix[1][3], m_matrix[2][3], m_matrix[3][3]);
	vec4 lb = m_matrix[0];
	vec4 lt = m_matrix[1];
	vec4 rt = m_matrix[2];
	vec4 rb = m_matrix[3];
	float xp = (pos.x - (-1)) / 2, yp = (pos.y - (-1)) / 2;
	vec4 l = (lt - lb) * yp + lb, r = (rt - rb) * yp + rb;
	vec4 newpos = (r - l) * xp + l;
	// newpos = vec4(pos.x, pos.y, 0, 1);
	gl_Position = proj_matrix * v_matrix * newpos;
	nxtpos = vec2(newpos.x, newpos.y);
} 
)";

const char* fshaderSource = R"(
#version 430

in vec2 nxtpos;
out vec4 color;

uniform vec4 bg_color;
uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 proj_matrix;
layout (binding=0) uniform sampler2D samp;

float cross(vec2 a, vec2 b) {
	return a.x * b.y - a.y * b.x;
}
vec2 inverse_bilinear(vec2 x, vec2 d, vec2 a, vec2 b, vec2 c) {
	vec2 e = b - a, f = d - a, g = a - b + c - d, h = x - a;
	float k2 = cross(g, f);
	float k1 = cross(e, f) + cross(h, g);
	float k0 = cross(h, e);
	if (abs(k2) < 0.0001) return vec2((h.x * k1 + f.x * k0) / (e.x * k1 - g.x * k0), -k0 / k1);

	float w2 = k1 * k1 - 4 * k0 * k2;
	if (w2 < 0) return vec2(-1, -1);
	float w = sqrt(w2);
	float ik2 = 0.5 / k2;
	float v = (-k1 - w) * ik2, u = (h.x - f.x * v) / (e.x + g.x * v);
	if (u < 0 || u > 1 || v < 0 || v > 1) {
		v = (-k1 + w) * ik2;
		u = (h.x - f.x * v) / (e.x + g.x * v);
	}
	return vec2(u, v);
}
void main(void)
{
	vec2 lb = m_matrix[0].xy;
	vec2 lt = m_matrix[1].xy;
	vec2 rt = m_matrix[2].xy;
	vec2 rb = m_matrix[3].xy;
	vec2 uv = inverse_bilinear(nxtpos, lb, lt, rt, rb);
	uv.y = 1 - uv.y;
	color = texture(samp, uv);
	color.r *= bg_color.r;
	color.g *= bg_color.g;
	color.b *= bg_color.b;
	color.a *= bg_color.a;
}
)";

glm::mat4 pMat;
GLuint vao[1];
GLuint vbo[1];
GLuint renderingProgram;

bool checkOpenGLError()  {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR)  {
		cout << "glError: " << glErr << endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

void printShaderLog(GLuint shader)  {
	int len = 0;
	int chWrittn = 0;
	char *log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)  {
		log = (char *)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		cout << "Shader Info Log: " << log << endl;
		free(log);
	}
}

GLuint prepareShader(int shaderTYPE, const char *shaderSrc) {
	GLint shaderCompiled;
	GLuint shaderRef = glCreateShader(shaderTYPE);

	if (shaderRef == 0 || shaderRef == GL_INVALID_ENUM) {
		printf("Error: Could not create shader of type:%d\n", shaderTYPE);
		return 0;
	}

	glShaderSource(shaderRef, 1, &shaderSrc, NULL);
	glCompileShader(shaderRef);
	checkOpenGLError();
	
	glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != GL_TRUE) {
		if (shaderTYPE == GL_VERTEX_SHADER) cout << "Vertex ";
		if (shaderTYPE == GL_TESS_CONTROL_SHADER) cout << "Tess Control ";
		if (shaderTYPE == GL_TESS_EVALUATION_SHADER) cout << "Tess Eval ";
		if (shaderTYPE == GL_GEOMETRY_SHADER) cout << "Geometry ";
		if (shaderTYPE == GL_FRAGMENT_SHADER) cout << "Fragment ";
		if (shaderTYPE == GL_COMPUTE_SHADER) cout << "Compute ";
		cout << "shader compilation error for shader." << endl;
		printShaderLog(shaderRef);
	}


	//====================================
	// Custom Compilation Error Checking
	//====================================
	checkOpenGLError();
	GLint compiled;
	glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &compiled);
	if (compiled != GL_TRUE) {
		printf("Error: Failed to compile shader.\n");

		GLint log_size = 0;
		glGetShaderiv(shaderRef, GL_INFO_LOG_LENGTH, &log_size);

		printf("Shader log length: %d\n", log_size);

		GLchar* info_log = (GLchar*)malloc(sizeof(GLchar)*log_size);
		glGetShaderInfoLog(shaderRef, log_size, &log_size, info_log);
		printf("Compilation Log: '%s'\n", info_log);
		// printf("First 5 chars: %d %d %d %d %d\n", info_log[0], info_log[1], info_log[2], info_log[3], info_log[4]);
		free(info_log);
		glDeleteShader(shaderRef);
		return 0;

	}
	//====================================
	return shaderRef;
}

void printProgramLog(int prog)  {
	int len = 0;
	int chWrittn = 0;
	char *log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char *)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		cout << "Program Info Log: " << log << endl;
		free(log);
	}
}

int finalizeShaderProgram(GLuint sprogram) {
	GLint linked;
	glLinkProgram(sprogram);
	checkOpenGLError();
	glGetProgramiv(sprogram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		cout << "linking failed" << endl;
		printProgramLog(sprogram);
	}
	return sprogram;
}

GLuint createShaderProgram() {
	GLuint vShader = prepareShader(GL_VERTEX_SHADER, vshaderSource);
	GLuint fShader = prepareShader(GL_FRAGMENT_SHADER, fshaderSource);
	GLuint vfprogram = glCreateProgram();
	glAttachShader(vfprogram, vShader);
	glAttachShader(vfprogram, fShader);
	finalizeShaderProgram(vfprogram);
	return vfprogram;
}

int origWidth, origHeight;
void opengl_onresize(GLFWwindow* window, int width, int height) {
	::width = width;
	::height = height;
	aspectRadio = 1.0 * width / height;
	pMat = glm::ortho(
		-1.0 * width / origWidth, 
		1.0 * width / origWidth, 
		-1.0 * height / origHeight, 
		1.0 * height / origHeight, 
		0.0, -1000000000.0
	);
	custom_onresize(width, height);
}

int mouseTouchId[8] = { 0 };
double mouseX, mouseY;
void opengl_onmousemove(GLFWwindow* window, double xpos, double ypos) {
	mouseX = xpos, mouseY = ypos;
	addGLEvent([](double time) {
		for (int i = 0; i < 8; i++) if (mouseTouchId[i] != 0) 
			updateTouch(mouseTouchId[i], time, (mouseX / width * 2 - 1) * aspectRadio, 1 - mouseY / height * 2 );
	});
}
void opengl_onmousepress(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		addGLEvent([button](double time) {
			mouseTouchId[button] = createTouch(time, (mouseX / width * 2 - 1) * aspectRadio, 1 - mouseY / height * 2);
		});
	} else if (action == GLFW_RELEASE) {
		addGLEvent([button](double time) {
			removeTouch(mouseTouchId[button], time, (mouseX / width * 2 - 1) * aspectRadio, 1 - mouseY / height * 2);
			mouseTouchId[button] = 0;
		});
	}
}

map<int, pair<double, double> > keyPos = {};
int keyTouchId[512] = { 0 };
void opengl_onkeypress(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (keyPos.count(key) == 0) return;
		addGLEvent([key](double time) {
			keyTouchId[key] = createTouch(time, keyPos[key].first, keyPos[key].second);
		});
	} else if (action == GLFW_RELEASE) {
		if (keyPos.count(key) == 0) return;
		addGLEvent([key](double time) {
			removeTouch(keyTouchId[key], time, keyPos[key].first, keyPos[key].second);
			keyTouchId[key] = 0;
		});
	}
}

void opengl_init() {
    if (use_x11) glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
	if (!glfwInit()) exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
	window = glfwCreateWindow(width, height, "Sonolus Debugger (sdb)", NULL, NULL);
	if (!window) {
        cerr << "glfwCreateWindow failed!" << endl;
        exit(EXIT_FAILURE);
    }
	glfwMakeContextCurrent(window);
	// glfwSetFramebufferSizeCallback(window, opengl_onresize);
	glfwSetCursorPosCallback(window, opengl_onmousemove);
	glfwSetMouseButtonCallback(window, opengl_onmousepress);
	glfwSetKeyCallback(window, opengl_onkeypress);
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
	auto err = glewInit();
	if (err != GLEW_OK && err != GLEW_ERROR_NO_GLX_DISPLAY) {
		cout << err << endl;
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

	renderingProgram = createShaderProgram();

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(1, vbo);
	float v[] = { 
		-1, -1, 0, 
		-1, 1, 0, 
		1, -1, 0,

		1, 1, 0, 
		1, -1, 0,
		-1, 1, 0, 
	};
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 9, v, GL_STATIC_DRAW);

	glfwGetFramebufferSize(window, &width, &height);
	origWidth = width, origHeight = height;
	aspectRadio = 1.0 * width / height;
	pMat = glm::ortho(-1, 1, -1, 1, 0, -1000000000);
	// pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

void display(double currentTime) {
	// while (pthread_mutex_trylock(&touchMtx)) usleep(10);
	// pthread_mutex_lock(&touchMtx);
	// pthread_mutex_unlock(&touchMtx);
	
	glUseProgram(renderingProgram);
	GLuint mLoc = glGetUniformLocation(renderingProgram, "m_matrix");
	GLuint vLoc = glGetUniformLocation(renderingProgram, "v_matrix");
	GLuint projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	GLuint colorLoc = glGetUniformLocation(renderingProgram, "bg_color");
	glm::mat4 vMat = glm::lookAt(glm::vec3({ 0, 0, 1 }), { 0, 0, 0 }, { 0, 1, 0 });
    
	vector<vector<ParticleDataEffect::DrawElement> > particles;
	int z = -renderDrawLists.size();
	for (const auto &v : activeEffects) {
		particles.push_back(v.second.getDrawLists(currentTime));
		z += particles.back().size();
	}

    for (int i = 0; i < renderDrawLists.size(); i++) {
        DrawElement e = renderDrawLists[i];
        if (textures.count(e.spriteId) == 0) continue;
		skinTransforms[e.spriteId].calc(e.x1, e.y1, e.x2, e.y2, e.x3, e.y3, e.x4, e.y4);
        glm::mat4 mMat = glm::mat4({
			{e.x1 / aspectRadio * width / origWidth, e.y1 * height / origHeight, z, 1 }, 
			{e.x2 / aspectRadio * width / origWidth, e.y2 * height / origHeight, z, 1 }, 
			{e.x3 / aspectRadio * width / origWidth, e.y3 * height / origHeight, z, 1 }, 
			{e.x4 / aspectRadio * width / origWidth, e.y4 * height / origHeight, z, 1 }, 
        });
		glm::vec4 color = glm::vec4({ 1.0, 1.0, 1.0, e.a });
        glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mMat));
        glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
        glUniform4fv(colorLoc, 1, glm::value_ptr(color));
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[e.spriteId].textureId);

        // glEnable(GL_CULL_FACE);
        // glFrontFace(GL_CCW);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

		z++;
    }
	for (int i = 0; i < particles.size(); i++) {
		for (int j = 0; j < particles[i].size(); j++) {
			const auto &e = particles[i][j];
			glm::mat4 mMat = glm::mat4({
				{e.x1 / aspectRadio * width / origWidth, e.y1 * height / origHeight, z, 1 }, 
				{e.x2 / aspectRadio * width / origWidth, e.y2 * height / origHeight, z, 1 }, 
				{e.x3 / aspectRadio * width / origWidth, e.y3 * height / origHeight, z, 1 }, 
				{e.x4 / aspectRadio * width / origWidth, e.y4 * height / origHeight, z, 1 }, 
			});
			// cout << e.x1 << " " << e.y1 << " " << e.x2 << " " << e.y2 << " " << e.x3 << " " << e.y3 << " " << e.x4 << " " << e.y4 << endl;
			glm::vec4 color = glm::vec4({ e.r, e.g, e.b, e.a });
			// cout << engineData["skin"]["sprites"][e.spriteId]["name"].asString() << " " << textures[e.spriteId].width << " " << textures[e.spriteId].height << " " << mMat << endl;
			glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mMat));
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
			glUniform4fv(colorLoc, 1, glm::value_ptr(color));
			
			glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, particleTextures[e.sprite].textureId);

			// glEnable(GL_CULL_FACE);
			// glFrontFace(GL_CCW);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);

			glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

			z++;
		}
	} // cout << endl;
}