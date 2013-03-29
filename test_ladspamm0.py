import ladspamm0

w = ladspamm0.world()

print ("Number of libraries:", len(w.libraries))

for lib in w.libraries:
	print("  File:", lib.the_dl.filename)
	print("  Number of plugins: ", len(lib.plugins))
	
	for plugin in lib.plugins:
		print("    Name:", plugin.name(), "Label:", plugin.label(), "Maker:", plugin.maker())
	
i = ladspamm0.plugin_instance(w.libraries[0].plugins[0], 48000)

print ("default:", i.port_default(0))



