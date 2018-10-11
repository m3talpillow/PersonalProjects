// GLSL (OpenGL shading Language)

THREE.CustomGrayScaleShader = {

    uniforms: {
        // Defining the typs for Js and their values
        "tDiffuse": { type: "t", value: null },
        "rPower":  { type: "f", value: 0.2126 },
        "gPower":  { type: "f", value: 0.7152 },
        "bPower":  { type: "f", value: 0.0722 }

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
        "uniform float rPower;",
        "uniform float gPower;",
        "uniform float bPower;",
        // Texture that contains the image fromt he previous EffectComposer pass
        "uniform sampler2D tDiffuse;",

        "varying vec2 vUv;",

        "void main() {",
        // Texture 2d takes the texture and the uv mamp and returns the
        // correct pixel color and opacity for each pixel.
        "vec4 texel = texture2D( tDiffuse, vUv );",
        // Modify the color
        "float gray = texel.r*rPower + texel.g*gPower + texel.b*bPower;",
        // Return the new fragmented pixel
        "gl_FragColor = vec4( vec3(gray), texel.w );",
        "}"
    ].join("\n")
};
