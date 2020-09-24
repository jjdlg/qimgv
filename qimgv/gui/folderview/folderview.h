#pragma once

#include <QWidget>
#include <QStyledItemDelegate>
#include <QAbstractItemView>
#include <QFileSystemModel>
#include <QFileDialog>
#include "gui/idirectoryview.h"
#include "gui/folderview/foldergridview.h"
#include "gui/folderview/filesystemmodelcustom.h"
#include "gui/folderview/bookmarkswidget.h"
#include "gui/customwidgets/actionbutton.h"
#include "gui/customwidgets/styledcombobox.h"

namespace Ui {
    class FolderView;
}

class FolderView : public QWidget, public IDirectoryView {
    Q_OBJECT
    Q_INTERFACES(IDirectoryView)
public:
    explicit FolderView(QWidget *parent = nullptr);
    ~FolderView();

public slots:
    void show();
    void hide();
    virtual void populate(int) override;
    virtual void setThumbnail(int pos, std::shared_ptr<Thumbnail> thumb) override;
    virtual void select(QList<int>) override;
    virtual void select(int) override;
    virtual QList<int> selection() override;
    virtual void focusOn(int) override;
    virtual void setDirectoryPath(QString path) override;
    virtual void insertItem(int index) override;
    virtual void removeItem(int index) override;
    virtual void reloadItem(int index) override;
    void addItem();
    void onFullscreenModeChanged(bool mode);
    void onSortingChanged(SortingMode mode);


protected:
    void wheelEvent(QWheelEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;

protected slots:
    void onShowLabelsChanged(bool mode);
    void onShowLabelsButtonToggled(bool mode);
    void onThumbnailSizeChanged(int newSize);
    void onZoomSliderValueChanged(int value);

signals:
    void itemActivated(int) override;
    void thumbnailsRequested(QList<int>, int, bool, bool) override;
    void draggedOut(QList<int>) override;
    void draggedToBookmarks(QList<int>) override;
    void sortingSelected(SortingMode);
    void directorySelected(QString path);
    void copyUrlsRequested(QList<QUrl>, QString path);
    void moveUrlsRequested(QList<QUrl>, QString path);

private slots:
    void onSortingSelected(int);
    void readSettings();

    void onTreeViewClicked(QModelIndex index);
    void onDroppedInByIndex(QList<QUrl>, QModelIndex index);
    void onDroppedIn(QList<QUrl>, QString dirPath);
    void toggleBookmarks();
    void toggleFilesystemView();
    void setPlacesPanel(bool mode);
    void onPlacesPanelButtonChecked(bool mode);
    void onBookmarkClicked(QString dirPath);
    void newBookmark();
    void fsTreeScrollToCurrent();

    void onSplitterMoved();
    void onHomeBtn();
    void onRootBtn();
private:
    Ui::FolderView *ui;
    FileSystemModelCustom *dirModel;
};
