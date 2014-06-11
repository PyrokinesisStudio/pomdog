#version 330

layout(location = 0) in vec4 PositionTextureCoord;

// per Instance
// {xy__} = position.xy
// {__zw} = scale.xy
layout(location = 1) in vec4 Translation;
// {xy__} = xy
// {__zw} = {width, height}
layout(location = 2) in vec4 SourceRect;
// {xy__} = originPivot.xy
// {__z_} = rotation
// {___w} = layerDepth
layout(location = 3) in vec4 OriginRotationDepth;
// {xyzw} = color.rgba
layout(location = 4) in vec4 Color;


out VertexData {
	vec2 TextureCoord;
	vec4 Color;
} Out;

//uniform SpriteInfo {
//	// per Instance
//	vec4 Translation;         // (position.xy, scale.xy)
//	vec4 SourceRect;          // (x, y, width, height)
//	vec4 OriginRotationDepth; // (originPivot.xy, rotation, layerDepth)
//};

uniform SpriteBatchConstants {
	mat4x4 Projection2D;
	// mat4x4(
	//  vec4(Projection2D[0].xyz, 0),
	//  vec4(Projection2D[1].xyz, 0),
	//  vec4(Projection2D[2].xyz, 0),
	//  vec4(InverseTextureWidth.xy, 0, 0))
};


void main()
{
	mat3x3 scaling = mat3x3(
		vec3(Translation.z * SourceRect.z, 0.0, 0.0),
		vec3(0.0, Translation.w * SourceRect.w, 0.0),
		vec3(0.0, 0.0, 1.0));

	float cosRotation = cos(OriginRotationDepth.z);
	float sinRotation = sin(OriginRotationDepth.z);
	mat3x3 rotate = mat3x3(
		vec3(cosRotation, -sinRotation, 0.0f),
		vec3(sinRotation, cosRotation, 0.0f),
		vec3(0.0f, 0.0f, 1.0f));

	mat3x3 translate = mat3x3(
		vec3(1.0, 0.0, Translation.x),
		vec3(0.0, 1.0, Translation.y),
		vec3(0.0, 0.0, 1.0));

//	mat3x3 projection = mat3x3(
//		vec3((2.0/Viewport.x), 0.0, 0.0),
//		vec3(0.0, (2.0/Viewport.y), 0.0),
//		vec3(0.0, 0.0, 1.0));

	mat3x3 transform = (((scaling * rotate) * translate) * mat3x3(Projection2D));
	
	vec3 position = (vec3(PositionTextureCoord.xy - OriginRotationDepth.xy, 1.0) * transform);

	gl_Position = vec4(position.xy, OriginRotationDepth.w, 1.0);
	
	Out.TextureCoord = (PositionTextureCoord.zw * SourceRect.zw + SourceRect.xy) * Projection2D[3].xy;
	Out.Color = Color;

	//Out.TextureCoord = PositionTextureCoord.zw;
}
