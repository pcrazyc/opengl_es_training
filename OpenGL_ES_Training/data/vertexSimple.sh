attribute vec4 Position;
attribute vec4 SourceColor;

varying vec4 DestinationColor;
uniform mat4 Projection;
uniform mat4 Modelview;
varying mediump vec3 pos;

void main(void) {
    DestinationColor = SourceColor;
    gl_Position = Projection*Modelview*Position;
	pos = Position.xyz;
}

/*attribute vec4 position;
uniform highp mat4 mat;
varying mediump vec2 pos;
void main() { 
	gl_Position = position * mat;
	pos = position.xy;
}*/