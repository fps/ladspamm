import ladspamm0

w = ladspamm0.world()

print (w.libraries)
print len(w.libraries)
print (w.libraries[0])
print (w.libraries[0].plugins)
print (w.libraries[0].plugins[0])
print (w.libraries[0].plugins[0].name())
print (w.libraries[0].plugins[0].port_lower_bound(0))

i = ladspamm0.plugin_instance(w.libraries[0].plugins[0], 48000)

print ("default:", i.port_default(0))



