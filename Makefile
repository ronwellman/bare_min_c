MAIN_DIR= ./
OUTPUT_DIR= ./output/
BOOK= bare_min_c.pdf

# These targets are not actually files
.PHONY: all $(OUTPUT_DIR) src_files documents clean 

# Targets
all: $(OUTPUT_DIR) src_files documents clean 

# Ensure output folder is present
$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)

# Ensure all source files compile
src_files:
	cd src && $(MAKE)

# Generate the PDF
documents:
	pdflatex main
	makeindex main.idx -s StyleInd.ist
	biber main
	pdflatex main
	pdflatex main
	@mv main.pdf $(OUTPUT_DIR)$(BOOK)

# Clean up temporary files
clean:
	@rm -f $(MAIN_DIR)*.acn $(MAIN_DIR)*.glg $(MAIN_DIR)*.glo $(MAIN_DIR)*.gls $(MAIN_DIR)*.glsdefs  $(MAIN_DIR)*.xdy $(MAIN_DIR)*.acr $(MAIN_DIR)*.ilg $(MAIN_DIR)*.blg $(MAIN_DIR)*.aux $(MAIN_DIR)*.dvi $(MAIN_DIR)*.lot $(MAIN_DIR)*.toc $(MAIN_DIR)*.lof $(MAIN_DIR)*.brf $(MAIN_DIR)*.out $(MAIN_DIR)*.bak $(MAIN_DIR)*.bcf $(MAIN_DIR)*.xml $(MAIN_DIR)*.ptc $(MAIN_DIR)*.idx
	cd src && $(MAKE) clean
