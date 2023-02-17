#include "GraphicEngine.h"
#include "OBJ3D.h"
#include "InputManager.h"


void GraphicEngine::CreateCOM(ID3D11Device* device, IDXGISwapChain1* swapChain, const SIZE& frameSize)
{
	CreateRenderTagert(device, swapChain);
	CreateSamplerState(device);
	CreateBlendState(device);
	CreateDepthStencilView(device, swapChain, frameSize);
	CreateDepthStencilState(device);
	CreateRasterizerState(device);
	CreateConstantBuffer(device);
	CreateShaderManager(device);
	CreateTextureManager();
	CreateFramebuffer(device, swapChain);
	


}


void GraphicEngine::Init()
{
	CreateLightManager();
	CreateTextFont();
	CreateCameraManager();
	SetSlotVSConstantBuffer();
	SetSlotPSConstantBuffer();
	SetSlotSampler();

	for (size_t i = 0; i < framebufferManager.get()->getSizeListFrameBuffer(); i++)
	{
		std::vector<ObjectDrawData*> dataBuffer;
		uninvisibleDataObjectsFrameBuffer.push_back(dataBuffer);
	}

	exitGame = false;

}

void GraphicEngine::Update(float elapsedTime)
{
	CheckChangeRunGameMode();
	lightManager.get()->Update();
	cameraManager.get()->update();
	static float a = 0;
	POINT p;
	GetCursorPos(&p);
	float mousePos[2];
	mousePos[0] = (float)(p.x);
	mousePos[1] = (float)(p.y);
#ifdef USE_IMGUI
	//ImGui::SetNextWindowPos({ 0,0 });
	ImGui::Begin("Debug");
	ImGui::SliderFloat2("Mouse Pos", &mousePos[0], 0, 1);

	ImGui::End();

#endif // !USE_IMGUI
	

	UpdateResources();
}


	


void GraphicEngine::Render()
{
	ClearRenderTagertAndDepthStencil({ 0.5f,0.5f,0.5f,1 });
	framebufferManager.get()->ClearAllBuffer(immediateContext.Get());
	framebufferManager.get()->DrawOnFrameBuffer(immediateContext.Get());
	framebufferManager.get()->BlitMainFrameBufferToScreen(immediateContext.Get());
	
	

}

GraphicEngine::~GraphicEngine()
{
	DeleteAllEffect();
}

void GraphicEngine::drawSkinnedMesh(SkinnedMesh* obj, const DirectX::XMFLOAT4X4 world, const VECTOR4& color, SkinnedMesh::animation::keyframe* key, const int& drawTurn, DrawStates& drawStates, int slotFrameBuffer)
{
	if (drawStates.drawType != DrawType::SKYBOX)
		drawStates.drawType = DrawType::SkinnedMeshObject;
	uninvisibleDataObjectsFrameBuffer[slotFrameBuffer].push_back(new SkinnedMeshData(obj, world, color, key, drawTurn, drawStates));
}

void GraphicEngine::drawEffect(std::string effName, const VECTOR3& position, const int& drawTurn, int slotFrameBuffer, float size, VECTOR3 rotation, float angle, VECTOR4 color)
{
	std::map<std::string, Effect*>::iterator fi = effects.find(effName);
	if (fi == effects.end())
		_ASSERT_EXPR(NULL, "Effect not had created");
	DrawStates drawState;
	drawState.blendState = BlendStates::Alpha;
	drawState.depthState = DepthStencilStates::DepthTestOn_DepthWriteOn;
	drawState.drawType = DrawType::EffectObject;
	drawState.rasterizerState = RasterizerStates::DrawTriangles_BackTrianglesOff_AntialiasedLineOn;
	drawState.samplerState = SamplerStates::Anisotropic;
	uninvisibleDataObjectsFrameBuffer[slotFrameBuffer].push_back(new EffectData(fi->second, position, rotation, color, size, drawTurn, angle, drawState));

}

void GraphicEngine::drawSprite3D(Sprite3D* sprite3D, const DirectX::XMFLOAT4X4 world, const VECTOR4& color, int drawTurn)
{
	size_t n = sprites3DList.size();
	if (n == 0) return;
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < sprites3DList.size(); j++)
			{
				if (sprites3DList[i]->drawTurn_ > sprites3DList[j]->drawTurn_)
				{
					ObjectDrawData* t = sprites3DList[i];
					sprites3DList[i] = sprites3DList[j];
					sprites3DList[j] = t;

				}
			}

		}
	}

	for (size_t i = 0; i < n; i++)
	{
		Sprite3DData* data = sprites3DList.at(i)->getSprite3D();
		data->sprite3D->render(immediateContext.Get(), data->world, data->color);
	}
}

void GraphicEngine::drawSpriteLate(Sprite* sprite, const VECTOR2& position, const VECTOR2& scale, const VECTOR4& color, const VECTOR2& texture_position, const VECTOR2& texture_size, const float& angle, const int& drawTurn, DrawStates& drawStates)
{
	const VECTOR2& size = { texture_size.x * scale.x,texture_size.y * scale.y };
	std::string contents = "";
	drawStates.drawType = DrawType::Picture;

	Object2DListLate.push_back(new SpritesData(sprite, position, size, color, texture_position, texture_size, angle, drawTurn, drawStates, contents));

}

void GraphicEngine::drawSpriteEarly(Sprite* sprite, const VECTOR2& position, const VECTOR2& scale, const VECTOR4& color, const VECTOR2& texture_position, const VECTOR2& texture_size, const float& angle, const int& drawTurn, DrawStates& drawStates)
{
	const VECTOR2& size = { texture_size.x * scale.x,texture_size.y * scale.y };
	std::string contents = "";
	drawStates.drawType = DrawType::Picture;

	Object2DListEarly.push_back(new SpritesData(sprite, position, size, color, texture_position, texture_size, angle, drawTurn, drawStates, contents));

}

void GraphicEngine::drawSpriteLate(Sprite* sprite, const VECTOR2& position, const VECTOR2& scale, const VECTOR4& color, const VECTOR2& texture_position, const VECTOR2& texture_size, const float& angle, const int& drawTurn)
{
	const VECTOR2& size = { texture_size.x * scale.x,texture_size.y * scale.y };
	std::string contents = "";
	DrawStates drawStates;
	drawStates.blendState = BlendStates::Alpha;
	drawStates.depthState = DepthStencilStates::DepthTestOff_DepthWriteOff;
	drawStates.rasterizerState = RasterizerStates::DrawTriangles_BackTrianglesOff_AntialiasedLineOff;
	drawStates.samplerState = SamplerStates::Linear;
	drawStates.drawType = DrawType::Picture;

	Object2DListLate.push_back(new SpritesData(sprite, position, size, color, texture_position, texture_size, angle, drawTurn, drawStates, contents));

}

void GraphicEngine::drawSpriteEarly(Sprite* sprite, const VECTOR2& position, const VECTOR2& scale, const VECTOR4& color, const VECTOR2& texture_position, const VECTOR2& texture_size, const float& angle, const int& drawTurn)
{
	const VECTOR2& size = { texture_size.x * scale.x,texture_size.y * scale.y };
	std::string contents = "";
	DrawStates drawStates;
	drawStates.blendState = BlendStates::Alpha;
	drawStates.depthState = DepthStencilStates::DepthTestOff_DepthWriteOff;
	drawStates.rasterizerState = RasterizerStates::DrawTriangles_BackTrianglesOff_AntialiasedLineOff;
	drawStates.samplerState = SamplerStates::Linear;
	drawStates.drawType = DrawType::Picture;

	Object2DListEarly.push_back(new SpritesData(sprite, position, size, color, texture_position, texture_size, angle, drawTurn, drawStates, contents));


}

void GraphicEngine::drawBackgroudSpriteLate(Sprite* sprite, const VECTOR2& position, const VECTOR2& size, const int& drawTurn)
{
	VECTOR4 color = { 1,1,1,1 };
	VECTOR2 texture_position = { 0,0 };
	float angle = 0;
	DrawStates drawStates;
	drawStates.blendState = BlendStates::Alpha;
	drawStates.depthState = DepthStencilStates::DepthTestOff_DepthWriteOff;
	drawStates.rasterizerState = RasterizerStates::DrawTriangles_BackTrianglesOff_AntialiasedLineOn;
	drawStates.samplerState = SamplerStates::Linear;
	std::string contents = "";
	drawStates.drawType = DrawType::BACKGROUND;
	Object2DListLate.push_back(new SpritesData(sprite, position, size, color, texture_position, { 1920,1080 }, angle, drawTurn, drawStates, contents));


}

void GraphicEngine::drawBackgroudSpriteEarly(Sprite* sprite, const VECTOR2& position, const VECTOR2& size, const int& drawTurn)
{
	VECTOR4 color = { 1,1,1,1 };
	VECTOR2 texture_position = { 0,0 };
	float angle = 0;
	DrawStates drawStates;
	drawStates.blendState = BlendStates::Alpha;
	drawStates.depthState = DepthStencilStates::DepthTestOff_DepthWriteOff;
	drawStates.rasterizerState = RasterizerStates::DrawTriangles_BackTrianglesOff_AntialiasedLineOn;
	drawStates.samplerState = SamplerStates::Linear;
	std::string contents = "";
	drawStates.drawType = DrawType::BACKGROUND;
	Object2DListEarly.push_back(new SpritesData(sprite, position, size, color, texture_position, { 1920,1080 }, angle, drawTurn, drawStates, contents));


}

void GraphicEngine::textOut(int textNo, const std::string contents, const VECTOR2& position, const float& size, const VECTOR4& color, const int& drawTurn, bool late)
{
	if (textNo > 7) return;
	std::shared_ptr<Sprite> sprite = sprites[textNo];
	DrawStates drawStates;
	drawStates.blendState = BlendStates::Alpha;
	drawStates.depthState = DepthStencilStates::DepthTestOn_DepthWriteOn;
	drawStates.rasterizerState = RasterizerStates::DrawTriangles_BackTrianglesOff_AntialiasedLineOn;
	drawStates.samplerState = SamplerStates::Anisotropic;
	drawStates.drawType = DrawType::Text;
	const VECTOR2 size_ = text_fonts_size[textNo] * size;
	const VECTOR2 texture_position = { 0,0 };
	float angle = 0;
	if (late)
	{
		Object2DListLate.push_back(new SpritesData(sprite.get(), position, size_, color, texture_position, size_, angle, drawTurn, drawStates, contents));
		return;
	}
	Object2DListEarly.push_back(new SpritesData(sprite.get(), position, size_, color, texture_position, size_, angle, drawTurn, drawStates, contents));

}

void GraphicEngine::drawDebugBounding(GeometricPrimitive* geo, const DirectX::XMFLOAT4X4 world, const VECTOR4& color, const int& type)
{
	drawDebugList.push_back(new GeometricPrimitiveData(geo, world, color, type));
}

Sprite* GraphicEngine::createSprite(const wchar_t* filename, ShaderData* shaderData)
{
	std::shared_ptr<Sprite> sp;
	if (shaderData == nullptr)
		sp.reset(new Sprite(Framework::get()->getDevice(), filename));
	else sp.reset(new Sprite(Framework::get()->getDevice(), filename, *shaderData));
	sprites.push_back(sp);
	return sprites.back().get();
}

Square* GraphicEngine::createSquare()
{
}

Sprite3D* GraphicEngine::createSprite3D(const wchar_t* filename)
{
	std::shared_ptr<Sprite3D> sp3D(nullptr);
	sp3D.reset(new Sprite3D(Framework::get()->getDevice(), filename));
	sprites3D.push_back(sp3D);
	return sprites3D.back().get();
}

void GraphicEngine::createEffect(const char* filename, std::string effName)
{
	std::map<std::string, Effect*>::iterator fi = effects.find(effName);
	if (fi != effects.end())
		return;
	Effect* e = new Effect(filename);

	effects.insert(std::pair<std::string, Effect*>(effName, e));
}


BoundingCapsule* GraphicEngine::createCapsuleDebug(const float& height, const float& weight, const VECTOR3& offset)
{
	BoundingCapsule* capsule = nullptr;
	capsule = new BoundingCapsule(Framework::get()->getDevice(), height, weight, offset);
	geometricPrimitive.push_back(std::shared_ptr<BoundingCapsule>(capsule));
	return capsule;
}

BoundingSphere* GraphicEngine::createSphereDebug(const float& radius, const VECTOR3& offset)
{
	BoundingSphere* sphere = nullptr;
	sphere = new BoundingSphere(Framework::get()->getDevice(), radius, offset);
	geometricPrimitive.push_back(std::shared_ptr<BoundingSphere>(sphere));
	return sphere;
}
Ray* GraphicEngine::createRay(const VECTOR3& begin, const VECTOR3& end, const VECTOR4& color, RayType Type)
{
	Ray* ray = nullptr;
	ray = new Ray(Framework::get()->getDevice(), begin, end, color, Type);
	geometricPrimitive.push_back(std::shared_ptr<Ray>(ray));
	return ray;
}


SkinnedMesh* GraphicEngine::createSkinnedMesh(const char* fbx_name, bool triangulate, SkinnedMeshObjectAxis axis, ShaderData shaderData, VECTOR3 offsetvertex)
{
	std::shared_ptr<SkinnedMesh> mesh(nullptr);
	mesh.reset(new SkinnedMesh(Framework::get()->getDevice(), fbx_name, triangulate, axis, shaderData, offsetvertex));
	skinnedMeshes.push_back(mesh);
	return skinnedMeshes.back().get();
}

void GraphicEngine::ResetRenderTagertAndDepthStencil()
{
	if (renderTargetView)
	{
		renderTargetView.Reset();
	}
	if (depthStencilView)
	{
		depthStencilView.Reset();
	}
}

void GraphicEngine::RemoveQueneObject()
{
	for (size_t i = 0; i < uninvisibleDataObjectsFrameBuffer.size(); i++)
	{
		for (auto& it : uninvisibleDataObjectsFrameBuffer[i])
		{
			SafeDelete(it);
		}
		uninvisibleDataObjectsFrameBuffer[i].clear();
	}


	for (int i = 0; i < invisibleDataObjects.size(); i++)
	{
		SafeDelete(invisibleDataObjects[i]);
	}
	invisibleDataObjects.clear();

	for (int i = 0; i < Object2DListLate.size(); i++)
	{
		SafeDelete(Object2DListLate[i]);
	}
	Object2DListLate.clear();

	for (int i = 0; i < Object2DListEarly.size(); i++)
	{
		SafeDelete(Object2DListEarly[i]);
	}
	Object2DListEarly.clear();

	for (auto it : drawDebugList)
		if (it) SafeDelete(it);
	drawDebugList.clear();
	for (auto it : sprites3DList)
		if (it)
			SafeDelete(it);
	sprites3DList.clear();
}

void GraphicEngine::Draw2D(bool late)
{
	std::vector<ObjectDrawData*>* list = &Object2DListLate;
	if (!late)
		list = &Object2DListEarly;
	size_t n = list->size();
	if (n == 0) return;
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < list->size(); j++)
			{
				if ((*list)[i]->drawTurn_ > (*list)[j]->drawTurn_)
				{
					ObjectDrawData* a = (*list)[i];
					(*list)[i] = (*list)[j];
					(*list)[j] = a;

				}
			}

		}
	}


	for (int i = 0; i < list->size(); i++)
	{
		SpritesData* data = (*list)[i]->getSpritesData();
		switch ((*list)[i]->drawState_.drawType)
		{
		case DrawType::BACKGROUND:
		{
			data->sprite_->render(immediateContext.Get(),
				data->position_.x, data->position_.y,
				data->size_.x, data->size_.y);
			break;
		}
		case DrawType::Picture:

			data->sprite_->render(immediateContext.Get(),
				data->position_.x, data->position_.y,
				data->size_.x, data->size_.y,
				data->color_.x, data->color_.y, data->color_.z, data->color_.w,
				data->angle_,
				data->texture_position_.x, data->texture_position_.y,
				data->texture_size_.x, data->texture_size_.y
			);
			break;
		case DrawType::Text:
			data->sprite_->textout(immediateContext.Get(), data->contents_, data->position_.x, data->position_.y,
				data->size_.x, data->size_.y, data->color_.x, data->color_.y, data->color_.z, data->color_.w
			);
			break;
		}
	}
}

void GraphicEngine::DrawAllUninvisibleObject(int frameBufferSlot)
{
	std::vector<ObjectDrawData*>* uninvisibleDataObjects = &uninvisibleDataObjectsFrameBuffer[frameBufferSlot];

	size_t n = uninvisibleDataObjects->size();
	if (n == 0) return;
	//if (n> 5)
	//Quicksort(data, 0, n-1);
	//else
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < uninvisibleDataObjects->size(); j++)
			{
				if (uninvisibleDataObjects->at(i)->drawTurn_ > uninvisibleDataObjects->at(j)->drawTurn_)
				{
					ObjectDrawData* a = (*uninvisibleDataObjects)[i];
					(*uninvisibleDataObjects)[i] = (*uninvisibleDataObjects)[j];
					(*uninvisibleDataObjects)[j] = a;

				}
			}

		}
	}


	for (int i = 0; i < (*uninvisibleDataObjects).size(); i++)
	{
		//m_immediate_context->OMSetBlendState(m_blend_states[(*uninvisibleDataObjects)[i]->drawState_.blendState], nullptr, 0xFFFFFFFF);
		//m_immediate_context->RSSetState(m_rasterizer_states[(*uninvisibleDataObjects)[i]->drawState_.rasterizerState]);
		//m_immediate_context->OMSetDepthStencilState(m_depth_stencil_states[(*uninvisibleDataObjects)[i]->drawState_.depthState], 1);

		switch ((*uninvisibleDataObjects)[i]->drawState_.drawType)
		{

		case DrawType::StaticMeshObject:
		{

			//const VECTOR3& rotation = (*uninvisibleDataObjects)[i]->getStaticMeshData()->rotation_;
			//const VECTOR3& position = (*uninvisibleDataObjects)[i]->getStaticMeshData()->position_;
			//const VECTOR4& color = (*uninvisibleDataObjects)[i]->getStaticMeshData()->color_;
			//const VECTOR3& size = (*uninvisibleDataObjects)[i]->getStaticMeshData()->size_;
			//DirectX::XMMATRIX S{ DirectX::XMMatrixScaling(size.x, size.y, size.z) };
			//DirectX::XMMATRIX R{ DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(rotation.x), DirectX::XMConvertToRadians(rotation.y), DirectX::XMConvertToRadians(rotation.z)) };
			//DirectX::XMMATRIX T{ DirectX::XMMatrixTranslation(position.x, position.y, position.z) };
			//DirectX::XMStoreFloat4x4(&world, S * R * T);
			//(*uninvisibleDataObjects)[i]->getStaticMeshData()->staticMesh_->render(m_immediate_context, world, color);
			//if ((*uninvisibleDataObjects)[i]->getStaticMeshData()->drawBoudingBox_)
			//{
			//	m_immediate_context->PSSetSamplers(2, 1, &m_sampler_states[SamplerStates::Linear]);
			//	m_immediate_context->OMSetBlendState(m_blend_states[BlendStates::Alpha], nullptr, 0xFFFFFFFF);
			//	m_immediate_context->RSSetState(m_rasterizer_states[RasterizerStates::DrawLines_BackLinesOn_AntialiasedLineOn]);
			//	m_immediate_context->OMSetDepthStencilState(m_depth_stencil_states[DepthStencilStates::DepthTestOn_DepthWriteOn], 1);
			//	VECTOR3 sizeMin = (*uninvisibleDataObjects)[i]->getStaticMeshData()->staticMesh_->boundingBox.getSizeMin();
			//	VECTOR3 sizeMax = (*uninvisibleDataObjects)[i]->getStaticMeshData()->staticMesh_->boundingBox.getSizeMax();
			//
			//	//geometric3DPrimitives[1]->renderBoudingBox(m_immediate_context.Get(), world, sizeMin, sizeMax, { 1,1,1,1 });
			//
			//}
			break;
		}
		case DrawType::SkinnedMeshObject:
		{
			SkinnedMeshData* data = (*uninvisibleDataObjects)[i]->getSkinnedMeshData();
			const VECTOR4& color = data->color_;


			const SkinnedMesh::animation::keyframe* key = nullptr;
			//if (data->skinnedMesh_->animation_clips.empty() != 0)
			key = (*uninvisibleDataObjects)[i]->getSkinnedMeshData()->keyframe_;

			if (key != nullptr)
				data->skinnedMesh_->render(immediateContext.Get(), data->world_, color, key);
			else data->skinnedMesh_->render(immediateContext.Get(), data->world_, color, 0);


			break;
		}



		case DrawType::EffectObject:
		{
			EffectData* effData = (*uninvisibleDataObjects)[i]->getEffectData();
			Effekseer::Handle handle = effData->eff_->Play(effData->position_, effData->scale_, effData->rotation_, effData->angle_);
			break;
		}
		case DrawType::SKYBOX:
		{
			//ShaderManager::get()->BeginDrawSkyBox(m_immediate_context, m_depth_stencil_states[DepthStencilStates::DepthTestOn_DepthWriteOn],
			//	m_blend_states[BlendStates::Alpha], m_rasterizer_states[RasterizerStates::CullingOpposition]);

			SkinnedMeshData* data = (*uninvisibleDataObjects)[i]->getSkinnedMeshData();
			const VECTOR4& color = data->color_;


			const SkinnedMesh::animation::keyframe* key = nullptr;
			//if (data->skinnedMesh_->animation_clips.empty() != 0)
			key = (*uninvisibleDataObjects)[i]->getSkinnedMeshData()->keyframe_;

			if (key != nullptr)
				data->skinnedMesh_->render(immediateContext.Get(), data->world_, color, key);
			else data->skinnedMesh_->render(immediateContext.Get(), data->world_, color, 0);




		}
		}

	}

}

void GraphicEngine::CreateRenderTagert(ID3D11Device* device, IDXGISwapChain1* swapChain)
{
	HRESULT hr{ S_OK };
	ID3D11Texture2D* back_buffer{};
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&back_buffer));
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

	hr = device->CreateRenderTargetView(back_buffer, NULL, renderTargetView.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

	back_buffer->Release();




}

void GraphicEngine::CreateDepthStencilView(ID3D11Device* device, IDXGISwapChain1* swapChain, const SIZE& frameSize)
{
	HRESULT hr{ S_OK };
	ID3D11Texture2D* depth_stencil_buffer{};
	D3D11_TEXTURE2D_DESC texture2d_desc{};
	texture2d_desc.Width = frameSize.cx;
	texture2d_desc.Height = frameSize.cy;
	texture2d_desc.MipLevels = 1;
	texture2d_desc.ArraySize = 1;
	texture2d_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	texture2d_desc.SampleDesc.Count = 1;
	texture2d_desc.SampleDesc.Quality = 0;
	texture2d_desc.Usage = D3D11_USAGE_DEFAULT;
	texture2d_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texture2d_desc.CPUAccessFlags = 0;
	texture2d_desc.MiscFlags = 0;
	hr = device->CreateTexture2D(&texture2d_desc, NULL, &depth_stencil_buffer);
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));


	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc{};
	depth_stencil_view_desc.Format = texture2d_desc.Format;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;
	hr = device->CreateDepthStencilView(depth_stencil_buffer, &depth_stencil_view_desc, depthStencilView.GetAddressOf());
	_ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

	depth_stencil_buffer->Release();


}

void GraphicEngine::CreateSamplerState(ID3D11Device* device)
{
	samplerStateManager.reset(new SamplerStateManager);
	samplerStateManager.get()->Init(device);

}

void GraphicEngine::CreateDepthStencilState(ID3D11Device* device)
{
	depthStencilStateManager.reset(new DepthStencilStateManager);
	depthStencilStateManager.get()->Init(device);
}

void GraphicEngine::CreateBlendState(ID3D11Device* device)
{
	blendStateManager.reset(new BlendStateManager);
	blendStateManager.get()->Init(device);
}

void GraphicEngine::CreateRasterizerState(ID3D11Device* device)
{
	rasterizerStateManager.reset(new RasterizerStateManager);
	rasterizerStateManager.get()->Init(device);
}

void GraphicEngine::CreateConstantBuffer(ID3D11Device* device)
{
	constantBufferManager.reset(new ConstantBufferManager);
	constantBufferManager.get()->Init(device);
}

void GraphicEngine::CreateFramebuffer(ID3D11Device* device, IDXGISwapChain1* swapChain)
{
	framebufferManager.reset(new FrameBufferManager);
	D3D11_VIEWPORT viewport;
	UINT num_viewports{ 1 };
	immediateContext.Get()->RSGetViewports(&num_viewports, &viewport);
	framebufferManager.get()->Init(swapChain, device,&viewport);
}

void GraphicEngine::CreateShaderManager(ID3D11Device* device)
{
	shaderManager.reset(new ShaderManager);
	shaderManager.get()->CreateShadowAllLayout(device);
}

void GraphicEngine::CreateTextureManager()
{
	textureManager.reset(new TextureManager);

}

void GraphicEngine::CreateLightManager()
{
	lightManager.reset(new LightManager);
	lightManager.get()->init({ 0,0,-1 }, { 1,1,1,1 }, { 0,0,10 });
}

void GraphicEngine::CreateCameraManager()
{
	cameraManager.reset(new CameraManager);
	cameraManager.get()->init();
}


void GraphicEngine::CreateTextFont()
{
	for (int i = 0; i < 8; i++)
	{
		createSprite(textFonts[i]);
	}
}

void GraphicEngine::CheckChangeRunGameMode()
{
	ControlPad* controlPad = InputManager::get()->getControlPad();
	//if (controlPad->PressF1(0));
	//if (controlPad->PressF2(0));

}


void GraphicEngine::SetSlotPSConstantBuffer()
{
	constantBufferManager.get()->setPSSlotNum(immediateContext.Get());
}

void GraphicEngine::SetSlotVSConstantBuffer()
{
	constantBufferManager.get()->setVSSlotNum(immediateContext.Get());
}

void GraphicEngine::UpdateResources()
{
	constantBufferManager.get()->updateResource(immediateContext.Get());
}

void GraphicEngine::SetSlotSampler()
{
	samplerStateManager.get()->setSamplerState(immediateContext.Get());
}

void GraphicEngine::ClearRenderTagertAndDepthStencil(const VECTOR4& color)
{
	FLOAT colorr[]{ color.x, color.y, color.z, color.w };
	immediateContext.Get()->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
	immediateContext.Get()->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	immediateContext.Get()->ClearRenderTargetView(renderTargetView.Get(), colorr);

}


void GraphicEngine::DeleteAllEffect()
{
	for (auto it : effects)
		if (it.second)
			delete it.second;
	effects.clear();
}

float GraphicEngine::getAspectRatio()
{
	D3D11_VIEWPORT viewport;
	UINT num_viewports{ 1 };
	immediateContext.Get()->RSGetViewports(&num_viewports, &viewport);
	return { viewport.Width / viewport.Height };
}

void GraphicEngine::getViewPort(D3D11_VIEWPORT* viewport)
{
	UINT num_viewports{ 1 };
	immediateContext.Get()->RSGetViewports(&num_viewports, viewport);
}
