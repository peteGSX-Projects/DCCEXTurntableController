# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))
import subprocess
import sphinx_rtd_theme

# Doxygen
subprocess.call('doxygen Doxyfile.in', shell=True)

# -- Project information -----------------------------------------------------

project = "DCC-EX Turntable Controller"
copyright = '2024, Peter Cole'
author = 'Peter Cole'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.autosectionlabel',
    'sphinxcontrib.spelling',
    'sphinx.ext.todo',
    'sphinx_sitemap',
    'sphinx_design',
    'breathe'
]

autosectionlabel_prefix_document = True

spelling_lang = 'en_AU'
tokenizer_lang = 'en_AU'
spelling_word_list_filename = ['spelling_wordlist.txt']

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

html_theme_options = {
    # 'style_nav_header_background': 'white',
    'logo_only': False,
    # Toc options
    'includehidden': True,
    'titles_only': True,
    'collapse_navigation': False,
    'navigation_depth': 3,
    'analytics_id': 'G-HBTV6STT77',
    'analytics_anonymize_ip': False,
    'prev_next_buttons_location': 'both',
}

html_context = {
    'display_github': True,
    'github_user': 'peteGSX-Projects',
    'github_repo': 'DCCEXTurntableController',
    'github_version': 'sphinx/docs/',
}

html_css_files = [
    'css/peteGSX-theme.css',
]

html_js_files = []

# Sphinx sitemap
html_baseurl = 'https://petegsx-projects.github.io/DCCEXTurntableController/'
html_extra_path = [
  'robots.txt',
  ]

# -- Breathe configuration -------------------------------------------------

breathe_projects = {
  "DCCEXTurntableController": "_build/xml/"
}
breathe_default_project = "DCCEXTurntableController"
breathe_default_members = ()
