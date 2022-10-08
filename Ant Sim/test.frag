uniform vec2 u_resolution;
uniform sampler2D u_texture;

void main() {
	vec4 screencol = texture2D(u_texture, gl_FragCoord.xy / vec2(1000, 700));
  gl_FragColor = screencol;
}