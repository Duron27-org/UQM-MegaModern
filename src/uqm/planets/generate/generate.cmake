############################################################


set(uqm_src_uqm_planets_generate_master_files "")


############################################################
# Local files
set(uqm_src_uqm_planets_generate_files
	"src/uqm/planets/generate/genall.h"
	"src/uqm/planets/generate/genand.cpp"
	"src/uqm/planets/generate/genburv.cpp"
	"src/uqm/planets/generate/genchmmr.cpp"
	"src/uqm/planets/generate/gencol.cpp"
	"src/uqm/planets/generate/gendefault.cpp"
	"src/uqm/planets/generate/gendefault.h"
	"src/uqm/planets/generate/gendru.cpp"
	"src/uqm/planets/generate/generate.cmake"
	"src/uqm/planets/generate/genilw.cpp"
	"src/uqm/planets/generate/genmel.cpp"
	"src/uqm/planets/generate/genmyc.cpp"
	"src/uqm/planets/generate/genorz.cpp"
	"src/uqm/planets/generate/genpet.cpp"
	"src/uqm/planets/generate/genpku.cpp"
	"src/uqm/planets/generate/genrain.cpp"
	"src/uqm/planets/generate/gensam.cpp"
	"src/uqm/planets/generate/genshof.cpp"
	"src/uqm/planets/generate/gensly.cpp"
	"src/uqm/planets/generate/gensol.cpp"
	"src/uqm/planets/generate/genspa.cpp"
	"src/uqm/planets/generate/gensup.cpp"
	"src/uqm/planets/generate/gensyr.cpp"
	"src/uqm/planets/generate/genthrad.cpp"
	"src/uqm/planets/generate/gentrap.cpp"
	"src/uqm/planets/generate/genutw.cpp"
	"src/uqm/planets/generate/genvault.cpp"
	"src/uqm/planets/generate/genvux.cpp"
	"src/uqm/planets/generate/genwreck.cpp"
	"src/uqm/planets/generate/genyeh.cpp"
	"src/uqm/planets/generate/genzfpscout.cpp"
	"src/uqm/planets/generate/genzoq.cpp"
)

source_group("src\\uqm\\planets\\generate" FILES ${uqm_src_uqm_planets_generate_files})
list(APPEND uqm_src_uqm_planets_generate_master_files ${uqm_src_uqm_planets_generate_files})
