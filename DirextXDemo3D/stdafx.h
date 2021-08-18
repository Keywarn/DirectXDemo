#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
#include <windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"
using namespace DirectX;

struct Vertex {
	Vertex(float x, float y, float z, float r, float g, float b, float a) : pos(x, y, z), colour(r, g, b, z) {}
	XMFLOAT3 pos;
	XMFLOAT4 colour;
};

struct ConstantBuffer {
	XMFLOAT4 colourMultiplier;
};

//Window data
HWND hwnd = NULL;
LPCTSTR WindowName = L"DirectX12DemoApp";
LPCTSTR WindowTitle = L"DirectX12 Demo Window";
int Width = 800;
int Height = 600;
bool FullScreen = false;
// exit the program when this becomes false
bool Running = true;

//only call release if an object exists (prevents exceptions calling release on non existant objects)
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }

//direct3D declarations
const int frameBufferCount = 3; //Number of buffers
ID3D12Device* device; //Device
IDXGISwapChain3* swapChain; //swapchain used to switch render targets
ID3D12CommandQueue* commandQueue; //Conitainer for command lists
ID3D12DescriptorHeap* rtvDescriptorHeap; //Descriptor heap to hold resources like render targets
ID3D12Resource* renderTargets[frameBufferCount]; //Number of render targets equal to buffer count
ID3D12CommandAllocator* commandAllocator[frameBufferCount]; //Enough allocators for each buffer * number of threads (only one)
ID3D12GraphicsCommandList* commandList; //A command list for putting commands into, execute to render frame
ID3D12Fence* fence[frameBufferCount]; //Object is locked while command list is being executed. Need as many as there are allocators
HANDLE fenceEvent; //Handle to an event when fence is unlocked
UINT64 fenceValue[frameBufferCount]; // Value is incremented with each frame, each fence has own value
int frameIndex; //current rtv
int rtvDescriptorSize; // Size of rtv descriptor on device

//Rendering globals
ID3D12PipelineState* pipelineStateObject;
ID3D12RootSignature* rootSignature;
D3D12_VIEWPORT viewport;
D3D12_RECT scissorRect;
ID3D12Resource* vertexBuffer;
D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
ID3D12Resource* indexBuffer;
D3D12_INDEX_BUFFER_VIEW indexBufferView;

ID3D12Resource* depthStencilBuffer;
ID3D12DescriptorHeap* dsDescriptorHeap;

//Root descriptor table stuff
ID3D12DescriptorHeap* mainDescriptorHeap[frameBufferCount];
ID3D12Resource* constantBufferUploadHeap[frameBufferCount];

ConstantBuffer cbColourMultiplierData;
UINT8* cbColourMultiplierGPUAddress[frameBufferCount];

//Initialize direct3d
bool InitD3D();
//Update game logic
void Update();
//Update direct3d pipeline (update command lists)
void UpdatePipeline();
//Execute command list
void Render();
//Rekease objects and clean memory
void Cleanup();
//Wait until GPU is finished with command list
void WaitForPreviousFrame();

//Create window
bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, bool fullscreen);

//Main Application loop
void mainloop();

//Callback for windows messages
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);