#include <iostream>
#include <NuakeRenderer/NuakeRenderer.h>

#include <Core.h>
#include <Slate.h>
#include <Dependencies/NuakeRenderer/Dependencies/imgui/imgui_internal.h>

struct LaunchSettings
{
    uint32_t Width;
    uint32_t Height;
    bool IsPlayer;
};

LaunchSettings _LaunchArguments;

void ParseArguments(int argc, char* argv[])
{
    if (argc == 1)
    {
        return;
    }
    
    for (uint32_t i = 0; i < argc; i++)
    {
        char* arg = argv[i];
        std::string argString = std::string(arg);

        if (argString == "-player")
        {
            _LaunchArguments.IsPlayer = true;
        }
        else if (argString == "-w" && i + 1 < argc)
        {
            std::string widthString = argv[++i];
            _LaunchArguments.Width = stoi(widthString);
        }
        else if (argString == "-h" && i + 1 < argc)
        {
            std::string heightString = argv[++i];
            _LaunchArguments.Height = stoi(heightString);
        }
    }
}

bool _dockingInit = false;

int main(int argc, char* argv[]) 
{
    ParseArguments(argc, argv);

    using namespace Core;
    using namespace NuakeRenderer;

    auto window = CreateWindow(_LaunchArguments.Width, _LaunchArguments.Height);
    // ImGui Flags and theme.
    ApplyNuakeImGuiTheme();
    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    Slate slate = Slate();

    RedNode redNode = RedNode();
    redNode.Register();

    redNode.SetInput<bool>("InputBool", false);
    redNode.Process();

    while (!window->ShouldClose())
    {
        PollEvents();
        Clear();

        Begin();
        BeginImGuiFrame();

		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.0f));
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		auto& io = ImGui::GetIO();
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		ImGui::Begin("Dockspace", nullptr, window_flags);
		{
			ImGui::PopStyleVar(3);

			ImGuiIO const& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("Dockspace");

				_dockingInit = ImGui::DockBuilderGetNode(dockspace_id) == NULL;
				ImGui::DockSpace(dockspace_id, ImVec2(0.f, 0.f), dockspace_flags);

				if (_dockingInit)
				{
					ImGuiID dock_main_id = dockspace_id;
					ImGuiID dock_id_prop_opp = 0;
					ImGuiID dock_id_prop = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, &dock_id_prop_opp, &dock_main_id);
					ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

					ImGui::DockBuilderDockWindow("inspector", dock_id_prop);
					ImGui::DockBuilderDockWindow("viewport", dock_main_id);
					ImGui::DockBuilderFinish(dockspace_id);
				}
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New", "CTRL+N"))
						//OpenImage();

						ImGui::Separator();

					if (ImGui::MenuItem("Export Image", "CTRL+E"))
					{
						

					}


					ImGui::Separator();

					if (ImGui::MenuItem("Exit", "CTRL+Q"))
					{


						std::terminate();
					}

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Options"))
				{
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
		}
		ImGui::End();

        EndImGuiFrame();
        window->SwapBuffers();
    }

    delete window;

    return EXIT_SUCCESS;
}