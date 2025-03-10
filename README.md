# osg-qt6

Demos Using QT6 and OSG/osgEarth

# HELP/ChatGPT Conversation(s)

- https://chatgpt.com/share/67cb6cb1-93e4-8002-bf29-d4b8f48778a1
- https://docs.osgearth.org/en/latest/faq.html#rendering-problems-when-using-the-qt-qopenglwidget

# TODO

- [x] Basic GL Example
- [x] Basic OSG Example (ignoring FFP setup)
- [ ] Basic OSG Example (assuming NO FFP)
- [x] Basic osgEarth3 Example (requiring FFP-less OSG)
- [ ] Non-trivial osgEarth3 Example (addressing FBO issue)

# NOTES

1. Compile and run the examples from a temporary build dir (so that the examples
   know how to find the toplevel data files, since they use `../world.tif` style
   paths).

2. *Futhermore*, if you check the osgEarth link above, you'll see some notes about
   needing to set/reset the "default FBO id" per-frame; I was able to get this
   simple example to work without doing so, but any non-trivial example will likely
   fail without it. I'm still looking into what EXACTLY the value is/should be that
   the `defaultFramebufferObject()` implies).

3. Finally, I'm using hard-coded paths in my (_CURRENT_) CMakeLists.txt setup,
   as it's not entirely clear at the moment what the "offical" way is to "find
   osgEarth" in CMake. Adjust for your needs.
