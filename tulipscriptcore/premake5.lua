project "tulipscriptcore"
    kind "SharedLib"
    language "C#"
    dotnetframework "4.7.2"

    targetdir ("../tulipscript/resources/scripts")
    objdir ("../tulipscript/resources/scripts-int")

    files {
        "src/**.cs"
    }