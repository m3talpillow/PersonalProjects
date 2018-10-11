// GLSL (OpenGL shading Language)

THREE.CustomBitShader = {

    uniforms: {
        // Defining the typs for Js and their values
        "tDiffuse": { type: "t", value: null },
        "bitSize":  { type: "i", value: 4 }
    },

    // Standard vertexShader b/c we don't want to move any vertecies around
    vertexShader: [
        "varying vec2 vUv;",
        "void main() {",
        "vUv = uv;",
        "gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );",
        "}"
    ].join("\n"),


    fragmentShader: [
        // Uniform means passing from Js to the Shader
        "uniform int bitSize;",
        // Texture that contains the image fromt he previous EffectComposer pass
        "uniform sampler2D tDiffuse;",

        "varying vec2 vUv;",

        "void main() {",
        // Texture 2d takes the texture and the uv map and returns the
        // correct pixel color and opacity for each pixel.
        "vec4 texel = texture2D( tDiffuse, vUv );",
        // Find new color using only n bit color range
        "float n = pow(float(bitSize), 2.0);",
        "float newR = floor(texel.r * n) / n;",
        "float newG = floor(texel.g * n) / n;",
        "float newB = floor(texel.b * n) / n;",
        "gl_FragColor = vec4(newR, newG, newB, texel.w);",
        "}"
    ].join("\n")
};
