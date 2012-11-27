varying lowp vec4 DestinationColor;
varying mediump vec3 pos;
uniform mediump float phase;

void main(void) {
    gl_FragColor = DestinationColor* sin((pos.x * pos.x + pos.y * pos.y + pos.z * pos.z) * 40.0 + phase);
}

/*varying mediump vec2 pos;
uniform mediump float phase;
void main() {
	gl_FragColor = vec4(1, 1, 1, 1) * sin((pos.x * pos.x + pos.y * pos.y) * 40.0 + phase);
}*/