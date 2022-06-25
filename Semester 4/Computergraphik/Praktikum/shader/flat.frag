#version 330 core

in vec3  fragmentColor;
in vec3  viewPosition;
out vec3 fragColor;

vec3 normals(vec3 pos) {
  vec3 fdx = dFdx(pos);
  vec3 fdy = dFdy(pos);
  return normalize(cross(fdx, fdy));
}

void main()
{
	fragColor = normals(viewPosition);
}

