#version 330 core

in vec3 vColor;
in vec2 vUV;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
    vec4 t = texture(tex, vUV);

    FragColor = t * vec4(vColor, 1.0);
}
